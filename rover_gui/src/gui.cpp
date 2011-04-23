#include <gtk/tk.h>

void on_status_destroy(GtkObject *object, gpointer user_data) {
	gtk_main_quit();
}

int main (int argc, char** argv) {
	GtkBuilder *builder;
	GtkWidget *window;
	
	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "gui.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "status"));
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));

	gtk_widget_show(window);
	gtk_main();

	return 0;
}
