#include <gtk/gtk.h>

#include "wiringPi.h"

enum ttl
{
    strobe = 36,
    data0 = 33,
    data1 = 38,
    data2 = 35,
    data3 = 40,
    data4 = 37
};

int setup()
{
    if (wiringPiSetupPhys() == -1)
    {
        return 1;
    }

    // pin mode settings
    pinMode(strobe, OUTPUT);
    pinMode(data0, OUTPUT);
    pinMode(data1, OUTPUT);
    pinMode(data2, OUTPUT);
    pinMode(data3, OUTPUT);
    pinMode(data4, OUTPUT);

    // init
    digitalWrite (strobe, HIGH);
    digitalWrite (data0, LOW);
    digitalWrite (data1, LOW);
    digitalWrite (data2, LOW);
    digitalWrite (data3, LOW);
    digitalWrite (data4, LOW);

    return 0;
}

void ttl(int num)
{
    // ttl
    digitalWrite (data0, 00001 & (num>>0));
    digitalWrite (data1, 00001 & (num>>1));
    digitalWrite (data2, 00001 & (num>>2));
    digitalWrite (data3, 00001 & (num>>3));
    digitalWrite (data4, 00001 & (num>>4));
    // strobe
    digitalWrite (strobe, LOW);
    digitalWrite (strobe, HIGH);
}

GtkWidget *g_lbl_hello;
GtkWidget *g_lbl_count;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "win_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_hello"));
    g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}

void on_btn_hello_clicked()
{
    static unsigned int count = 0;
    char str_count[30] = {0};
    
    gtk_label_set_text(GTK_LABEL(g_lbl_hello), "Hello, world!");
    count++;
    sprintf(str_count, "%d", count);
    gtk_label_set_text(GTK_LABEL(g_lbl_count), str_count);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
