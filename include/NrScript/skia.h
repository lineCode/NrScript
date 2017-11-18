﻿/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : 1. NrScript库中所有char常量字符串(文字、符号)必须限定为英文 
 *        2. 与特定系统平台相关的代码，请放入platform目录中
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 * !不要在此引入平台相关的头文件，
 */

#ifndef _NRSCRIPT_SKIA_H_
#define _NRSCRIPT_SKIA_H_ 1

#ifndef NRSCRIPT_BUILD_PLATFORM_LINUX
    #pragma warning(push)
    #pragma warning(disable:4244)
#endif

#include "skia/android/SkAndroidFrameworkUtils.h"
#include "skia/android/SkBRDAllocator.h"
#include "skia/android/SkBitmapRegionDecoder.h"
#include "skia/c/sk_canvas.h"
#include "skia/c/sk_data.h"
#include "skia/c/sk_image.h"
#include "skia/c/sk_maskfilter.h"
#include "skia/c/sk_matrix.h"
#include "skia/c/sk_paint.h"
#include "skia/c/sk_path.h"
#include "skia/c/sk_picture.h"
#include "skia/c/sk_shader.h"
#include "skia/c/sk_surface.h"
#include "skia/c/sk_types.h"
#include "skia/codec/SkAndroidCodec.h"
#include "skia/codec/SkCodec.h"
#include "skia/codec/SkCodecAnimation.h"
#include "skia/codec/SkEncodedInfo.h"
#include "skia/config/SkUserConfig.h"
#include "skia/core/SkAnnotation.h"
#include "skia/core/SkBBHFactory.h"
#include "skia/core/SkBitmap.h"
#include "skia/core/SkBlendMode.h"
#include "skia/core/SkBlurTypes.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkClipOp.h"
#include "skia/core/SkColor.h"
#include "skia/core/SkColorFilter.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkColorSpace.h"
#include "skia/core/SkColorSpaceXform.h"
#include "skia/core/SkColorSpaceXformCanvas.h"
#include "skia/core/SkData.h"
#include "skia/core/SkDataTable.h"
#include "skia/core/SkDeferredDisplayListRecorder.h"
#include "skia/core/SkDeque.h"
#include "skia/core/SkDocument.h"
#include "skia/core/SkDrawFilter.h"
#include "skia/core/SkDrawLooper.h"
#include "skia/core/SkDrawable.h"
#include "skia/core/SkEncodedImageFormat.h"
#include "skia/core/SkExecutor.h"
#include "skia/core/SkFilterQuality.h"
#include "skia/core/SkFlattenable.h"
#include "skia/core/SkFlattenableSerialization.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkFontArguments.h"
#include "skia/core/SkFontLCDConfig.h"
#include "skia/core/SkFontStyle.h"
#include "skia/core/SkGraphics.h"
#include "skia/core/SkICC.h"
#include "skia/core/SkImage.h"
#include "skia/core/SkImageDeserializer.h"
#include "skia/core/SkImageEncoder.h"
#include "skia/core/SkImageFilter.h"
#include "skia/core/SkImageGenerator.h"
#include "skia/core/SkImageInfo.h"
#include "skia/core/SkMallocPixelRef.h"
#include "skia/core/SkMask.h"
#include "skia/core/SkMaskFilter.h"
#include "skia/core/SkMath.h"
#include "skia/core/SkMatrix.h"
#include "skia/core/SkMatrix44.h"
#include "skia/core/SkMetaData.h"
#include "skia/core/SkMilestone.h"
#include "skia/core/SkMultiPictureDraw.h"
#include "skia/core/SkOverdrawCanvas.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkPathEffect.h"
#include "skia/core/SkPathMeasure.h"
#include "skia/core/SkPicture.h"
#include "skia/core/SkPictureAnalyzer.h"
#include "skia/core/SkPictureRecorder.h"
#include "skia/core/SkPixelRef.h"
#include "skia/core/SkPixelSerializer.h"
#include "skia/core/SkPixmap.h"
#include "skia/core/SkPngChunkReader.h"
#include "skia/core/SkPoint.h"
#include "skia/core/SkPoint3.h"
#include "skia/core/SkPostConfig.h"
#include "skia/core/SkPreConfig.h"
#include "skia/core/SkRRect.h"
#include "skia/core/SkRSXform.h"
#include "skia/core/SkRWBuffer.h"
#include "skia/core/SkRasterHandleAllocator.h"
#include "skia/core/SkRasterizer.h"
#include "skia/core/SkRect.h"
#include "skia/core/SkRefCnt.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkScalar.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkSize.h"
#include "skia/core/SkStream.h"
#include "skia/core/SkString.h"
#include "skia/core/SkStrokeRec.h"
#include "skia/core/SkSurface.h"
#include "skia/core/SkSurfaceProps.h"
#include "skia/core/SkSwizzle.h"
#include "skia/core/SkTLazy.h"
#include "skia/core/SkTextBlob.h"
#include "skia/core/SkTime.h"
#include "skia/core/SkTraceMemoryDump.h"
#include "skia/core/SkTypeface.h"
#include "skia/core/SkTypes.h"
#include "skia/core/SkUnPreMultiply.h"
#include "skia/core/SkVertices.h"
#include "skia/core/SkWriteBuffer.h"
#include "skia/core/SkWriter32.h"
#include "skia/core/SkYUVSizeInfo.h"
#include "skia/effects/Sk1DPathEffect.h"
#include "skia/effects/Sk2DPathEffect.h"
#include "skia/effects/SkAlphaThresholdFilter.h"
#include "skia/effects/SkArithmeticImageFilter.h"
#include "skia/effects/SkBlurDrawLooper.h"
#include "skia/effects/SkBlurImageFilter.h"
#include "skia/effects/SkBlurMaskFilter.h"
#include "skia/effects/SkColorFilterImageFilter.h"
#include "skia/effects/SkColorMatrix.h"
#include "skia/effects/SkColorMatrixFilter.h"
#include "skia/effects/SkComposeImageFilter.h"
#include "skia/effects/SkCornerPathEffect.h"
#include "skia/effects/SkDashPathEffect.h"
#include "skia/effects/SkDiscretePathEffect.h"
#include "skia/effects/SkDisplacementMapEffect.h"
#include "skia/effects/SkDropShadowImageFilter.h"
#include "skia/effects/SkGradientShader.h"
#include "skia/effects/SkHighContrastFilter.h"
#include "skia/effects/SkImageSource.h"
#include "skia/effects/SkLayerDrawLooper.h"
#include "skia/effects/SkLayerRasterizer.h"
#include "skia/effects/SkLightingImageFilter.h"
#include "skia/effects/SkLumaColorFilter.h"
#include "skia/effects/SkMagnifierImageFilter.h"
#include "skia/effects/SkMatrixConvolutionImageFilter.h"
#include "skia/effects/SkMergeImageFilter.h"
#include "skia/effects/SkMorphologyImageFilter.h"
#include "skia/effects/SkOffsetImageFilter.h"
#include "skia/effects/SkOverdrawColorFilter.h"
#include "skia/effects/SkPaintFlagsDrawFilter.h"
#include "skia/effects/SkPaintImageFilter.h"
#include "skia/effects/SkPerlinNoiseShader.h"
#include "skia/effects/SkPictureImageFilter.h"
#include "skia/effects/SkRRectsGaussianEdgeMaskFilter.h"
#include "skia/effects/SkTableColorFilter.h"
#include "skia/effects/SkTableMaskFilter.h"
#include "skia/effects/SkTileImageFilter.h"
#include "skia/effects/SkToSRGBColorFilter.h"
#include "skia/effects/SkXfermodeImageFilter.h"
#include "skia/encode/SkEncoder.h"
#include "skia/encode/SkJpegEncoder.h"
#include "skia/encode/SkPngEncoder.h"
#include "skia/encode/SkWebpEncoder.h"
#include "skia/gpu/gl/GrGLAssembleInterface.h"
#include "skia/gpu/gl/GrGLConfig.h"
#include "skia/gpu/gl/GrGLExtensions.h"
#include "skia/gpu/gl/GrGLFunctions.h"
#include "skia/gpu/gl/GrGLInterface.h"
#include "skia/gpu/gl/GrGLTypes.h"
#include "skia/gpu/GrBackendSemaphore.h"
#include "skia/gpu/GrBackendSurface.h"
#include "skia/gpu/GrBlend.h"
#include "skia/gpu/GrCaps.h"
#include "skia/gpu/GrColor.h"
#include "skia/gpu/GrConfig.h"
#include "skia/gpu/GrContext.h"
#include "skia/gpu/GrContextOptions.h"
#include "skia/gpu/GrGpuResource.h"
#include "skia/gpu/GrRenderTarget.h"
#include "skia/gpu/GrResourceKey.h"
#include "skia/gpu/GrSamplerState.h"
#include "skia/gpu/GrShaderCaps.h"
#include "skia/gpu/GrSurface.h"
#include "skia/gpu/GrTexture.h"
#include "skia/gpu/GrTypes.h"
#include "skia/pathops/SkPathOps.h"
#include "skia/ports/SkFontConfigInterface.h"
#include "skia/ports/SkFontMgr.h"
#include "skia/ports/SkFontMgr_FontConfigInterface.h"
#include "skia/ports/SkFontMgr_android.h"
#include "skia/ports/SkFontMgr_directory.h"
#include "skia/ports/SkFontMgr_empty.h"
#include "skia/ports/SkFontMgr_indirect.h"
#include "skia/ports/SkRemotableFontMgr.h"
#include "skia/ports/SkTypeface_mac.h"
#include "skia/ports/SkTypeface_win.h"
#include "skia/svg/SkSVGCanvas.h"
#include "skia/utils/mac/SkCGUtils.h"
#include "skia/utils/SkCamera.h"
#include "skia/utils/SkCanvasStateUtils.h"
#include "skia/utils/SkDumpCanvas.h"
#include "skia/utils/SkEventTracer.h"
#include "skia/utils/SkFrontBufferedStream.h"
#include "skia/utils/SkInterpolator.h"
#include "skia/utils/SkLua.h"
#include "skia/utils/SkLuaCanvas.h"
#include "skia/utils/SkNWayCanvas.h"
#include "skia/utils/SkNoDrawCanvas.h"
#include "skia/utils/SkNullCanvas.h"
#include "skia/utils/SkPaintFilterCanvas.h"
#include "skia/utils/SkParse.h"
#include "skia/utils/SkParsePath.h"
#include "skia/utils/SkRandom.h"
#include "skia/utils/SkShadowUtils.h"
#include "skia/utils/SkTextBox.h"

#ifndef NRSCRIPT_BUILD_PLATFORM_LINUX
    #pragma warning(push)
#endif

#endif
