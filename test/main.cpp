#include <stdio.h>
#include <NrScript/base.h>

int bbb(int a, int b) {
    return a + b + 1000;
}

int bbbb2(int a, int b) {int i = 0; return 1;};

struct abc {
    int a;
    int b;
    int c;
    int d;
};

class NrTEst {
public:
    NrTEst() {
        e.add(this, &NrTEst::say);
        e.add(this, &NrTEst::say);
        e.add(bbb);
        e.add(this, &NrTEst::say2);
        x.add(this, &NrTEst::bbbb);
        x.add(bbbb2);

        auto func = [](int a, int b)->int {
            return a * b;
        };

        e.add(func);

        e.contains(func);
        e.contains(this, &NrTEst::say2);

        e.add([](int a, int b)->int{
            return a * b * 10000;
        });
    }

    int say(int a, int b) {
        e.remove(this, &NrTEst::say);
        return a + b;
    }

    int say2(int a, int b) {
        e.remove(this, &NrTEst::say2);
        return 0;
    }

    int bbbb(int a, int b) {
        int c = a + b;

        return 0;
    }

    int doTEST() {
        x(4, 4);
        
        return e(2, 3);
    }

    NrEvent<int(int, int)> e;
    NrEvent<int(int, int)> x;

private:
    abc _abc;
};

int main(int argc, char** argv) {

    NrTEst t {};
    int c = t.doTEST();

    return 0;
}