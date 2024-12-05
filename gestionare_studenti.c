#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTI 100
#define MAX_NUME 50

typedef struct {
    int id;
    char nume[MAX_NUME];
    float medie;
} Student;

Student studenti[MAX_STUDENTI];
int nrStudenti = 0;

// Funcții pentru gestionarea studenților
void adauga_student(const char *nume, float medie) {
    if (nrStudenti >= MAX_STUDENTI) {
        printf("Lista este plina.\n");
        return;
    }

    Student nou;
    nou.id = nrStudenti + 1;
    strcpy(nou.nume, nume);
    nou.medie = medie;

    studenti[nrStudenti++] = nou;
}

// Callback pentru butonul de adăugare cu afișare automată
void on_add_student_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **widgets = (GtkWidget **)data;

    GtkWidget *entry_name = widgets[0];
    GtkWidget *entry_grade = widgets[1];
    GtkWidget *text_view = widgets[2];

    // Obține textul din entry-uri
    const char *nume = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *medie_str = gtk_entry_get_text(GTK_ENTRY(entry_grade));

    // Verifică dacă numele este gol
    if (strlen(nume) == 0 || strlen(medie_str) == 0) {
        printf("Eroare: Numele sau media nu pot fi goale.\n");
        return;
    }

    float medie = atof(medie_str);

    // Adaugă studentul
    adauga_student(nume, medie);

    // Resetează câmpurile
    gtk_entry_set_text(GTK_ENTRY(entry_name), "");
    gtk_entry_set_text(GTK_ENTRY(entry_grade), "");

    // Actualizează zona de afișare a studenților
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "", -1); // Golește buffer-ul

    char student_info[256];
    for (int i = 0; i < nrStudenti; i++) {
        snprintf(student_info, sizeof(student_info), "ID: %d | Nume: %s | Medie: %.2f\n",
                 studenti[i].id, studenti[i].nume, studenti[i].medie);

        GtkTextIter iter;
        gtk_text_buffer_get_end_iter(buffer, &iter); // Obține un iterator nou la final
        gtk_text_buffer_insert(buffer, &iter, student_info, -1);
    }

    // Mesaj de confirmare în terminal
    printf("Student adaugat: %s, Medie: %.2f\n", nume, medie);
}


// Funcție pentru ștergerea tuturor studenților
void sterge_studenti(GtkWidget *widget, gpointer data) {
    // Resetează numărul de studenți
    nrStudenti = 0;

    // Golește zona text
    GtkWidget *text_view = GTK_WIDGET(data);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "", -1);

    printf("Toți studenții au fost șterși.\n");
}



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Fereastra principală
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Gestionare Studenti");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Layout vertical
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Intrări pentru adăugare student
    GtkWidget *entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), "Nume student");
    GtkWidget *entry_grade = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_grade), "Medie student");

    gtk_box_pack_start(GTK_BOX(vbox), entry_name, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_grade, FALSE, FALSE, 0);

    // Zonă text pentru afișarea listei
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    // Buton pentru adăugare student cu afișare automată
    GtkWidget *btn_add = gtk_button_new_with_label("Adauga Student");
    GtkWidget *widgets[] = {entry_name, entry_grade, text_view};
    g_signal_connect(btn_add, "clicked", G_CALLBACK(on_add_student_clicked), widgets);
    gtk_box_pack_start(GTK_BOX(vbox), btn_add, FALSE, FALSE, 0);

    // Buton pentru ștergerea tuturor studenților
    GtkWidget *btn_delete_all = gtk_button_new_with_label("Sterge Toți Studenții");
    g_signal_connect(btn_delete_all, "clicked", G_CALLBACK(sterge_studenti), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), btn_delete_all, FALSE, FALSE, 0);

    // Afișarea ferestrei
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}



