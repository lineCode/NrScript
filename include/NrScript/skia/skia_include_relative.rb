require 'pathname'

$include_dirs = []
$include_files = []
$line = 0

def dirTraverse(filePath, include_dirs)
	if File.directory? filePath
		Dir.foreach(filePath) do |dir|
			subPath = filePath + "/" + dir
			if dir != "." and dir !=".."
				if File.directory? subPath
					dirTraverse(subPath, include_dirs)
					include_dirs.push(subPath)
				end
			end
		end
	end
end

def fileTraverse(filePath, include_files)
	if File.directory? filePath
		Dir.foreach(filePath) do |f|
			subFilePath = filePath + "/" + f
			if f != "." and f != ".." and !File.directory? subFilePath
				include_files.push(subFilePath);
				#puts subFilePath
			end
		end
	end
end

$find_include_but_no_headers = []
$find_headers_but_no_match = []
$find_headers_but_match_fail = []

$line = 1
def enumFiles
	dirTraverse(".", $include_dirs)
	$include_dirs.each do |d|
		fileTraverse(d, $include_files)
	end

	$include_files.each do |f|
		lines = IO.readlines(f);
		File.open(f, "w+") do |file_writer|
			lines.each { |eLine|
				if eLine.index("#include") != nil
					line = eLine.reverse

					begin_find = false;

					header_file = "";
					line.each_char do |c|
						if begin_find 
							if c == "<" || c == "\"" || c == "/" || c == "\\"
								break;
							end
						end
						
						if begin_find
							header_file = header_file + c;
						end
						
						if c == ">" || c == "\""
							begin_find = true
						end
					end

					absPath = "";
					if !header_file.empty?
						$include_files.each do |inc|
							inc = inc.reverse
							if inc.index(header_file) == 0 and inc[header_file.length] == "/"
								print ($line.to_s.ljust(5) + "  " + f).ljust(50)
								print "#include-> "
								print header_file.reverse.ljust(50)
								print inc.reverse.ljust(50)
								
								
								pF = Pathname.new(f);
								pInc = Pathname.new(inc.reverse);
								absPath = pInc.relative_path_from(pF.parent);

								print absPath.to_s.ljust(50)
								puts (line.reverse)

								$line = $line+1
								break;
							end
						end
					else
						$find_include_but_no_headers.push(f.ljust(50) + eLine.chomp)
					end

					if !absPath.to_s.empty?
						regx = %r"#include\s+[\"<][\.+/]*[\w+/+]*\w+\.\w+[\">]"
						if (regx.match(eLine))
							eLine = eLine.to_s.sub(regx, "#include \"" + absPath.to_s + "\"")
						else
							$find_headers_but_match_fail.push(f.ljust(50) + eLine.chomp.ljust(50))
						end
					else
						$find_headers_but_no_match.push(f.ljust(50) + "\""+header_file.reverse+"\"".ljust(50) + eLine.chomp)
					end;
					
				end
				file_writer.syswrite(eLine);
			}
			file_writer.close
		end
	end

puts()
$find_include_but_no_headers.each do |s|
	puts "发现#include但没有头文件 ".ljust(35) + s
end

puts()
$find_headers_but_no_match.each do |s|
	puts "发现头文件但没有匹配 ".ljust(35) + s
end

puts()
$find_headers_but_match_fail.each do |s|
	puts "发现头文件匹配失败 ".ljust(35) + s
end
	
end

enumFiles


