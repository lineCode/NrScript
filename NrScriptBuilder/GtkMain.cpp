#include <gtk/gtk.h>
#include "NrBuilderApp.h"

int main(int argc, char** argv) {
    gtk_init(&argc, &argv);

    NrBuilderApp* app = new NrBuilderApp();
    if (!app) {
        return -1;
    }
    app->initialize();
    {
        char* msg = "体系结构";
        msg = "";
    }
    gtk_main();
    return 0;
}