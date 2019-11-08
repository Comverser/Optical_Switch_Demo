#include <gtk/gtk.h>
#include "wiringPi.h"

enum ttl
{
    reset = 8,
    strobe = 36,
    data0 = 33,
    data1 = 38,
    data2 = 35,
    data3 = 40,
    data4 = 37
};

int ttl_setup()
{
    if (wiringPiSetupPhys() == -1)
    {
        return 1;
    }

    // pin mode settings
    pinMode(reset, OUTPUT);
    pinMode(strobe, OUTPUT);
    pinMode(data0, OUTPUT);
    pinMode(data1, OUTPUT);
    pinMode(data2, OUTPUT);
    pinMode(data3, OUTPUT);
    pinMode(data4, OUTPUT);

    // init
    digitalWrite (reset, HIGH);
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
    if ( num == 0 )
    {
        digitalWrite (reset, LOW);
    }
    else if ( num >= 1 )
    {
        num--;
        // normal switch operation
        digitalWrite (reset, HIGH);
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
}

typedef struct
{
    GtkWidget *w_sb_ch;
    GtkWidget *w_sw_pwr;
    GtkWidget *w_lbl;
} app_wdgts;

int main(int argc, char *argv[])
{
    //---------------------------------------- general
    ttl_setup();
    ttl(0);

    //---------------------------------------- gui
    GtkBuilder      *builder; 
    GtkWidget       *window;

    // instantiate structure, allocating memory for it
    app_wdgts *od_wdgts= g_slice_new(app_wdgts);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "win_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "win_main"));

    od_wdgts->w_sb_ch = GTK_WIDGET(gtk_builder_get_object(builder, "sb_ch"));
    od_wdgts->w_sw_pwr = GTK_WIDGET(gtk_builder_get_object(builder, "sw_power"));
    od_wdgts->w_lbl = GTK_WIDGET(gtk_builder_get_object(builder, "lbl"));

    // widgets pointer will be passed to all widget handler functions as the user_data parameter
    gtk_builder_connect_signals(builder, od_wdgts);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    // free up memory used by widget structure, probably not necessary as OS wil reclaim memory from application after it exits
    g_slice_free(app_wdgts, od_wdgts);

    return 0;
}

void on_sb_ch_value_changed(GtkSpinButton *spin_button, app_wdgts *p_app_wdgts)
{
    if( gtk_switch_get_active(GTK_SWITCH(p_app_wdgts->w_sw_pwr)) )
    {
        guint32 ch_no = 0; // stores integer read from spin button widget
        ch_no = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(p_app_wdgts->w_sb_ch));
        gchar str_ch_no[30] = {0}; // buffer for string
        g_snprintf(str_ch_no, sizeof(str_ch_no), "Channel %d on", ch_no);
        gtk_label_set_text(GTK_LABEL(p_app_wdgts->w_lbl), str_ch_no);

        ttl(ch_no);
    }
}


void on_sw_power_state_set(GtkSwitch *widget, gboolean state, app_wdgts *p_app_wdgts)
{
    if (state)
    {
        guint32 ch_no = 0; // stores integer read from spin button widget
        ch_no = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(p_app_wdgts->w_sb_ch));
        gchar str_ch_no[30] = {0}; // buffer for string
        g_snprintf(str_ch_no, sizeof(str_ch_no), "Channel %d on", ch_no);
        gtk_label_set_text(GTK_LABEL(p_app_wdgts->w_lbl), str_ch_no);

        ttl(ch_no);
    }
}

// called when window is closed
void on_win_main_destroy()
{
    gtk_main_quit();
}
