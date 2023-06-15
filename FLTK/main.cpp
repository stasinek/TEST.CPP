#include <FLTK/Window.H>
#include <FLTK/Input.H>
#include <FLTK/Output.H>
#include <FLTK/Multiline_Input.H>
#include <FLTK/Multiline_Output.H>
#include <FLTK/Text_Display.H>
#include <FLTK/Text_Editor.H>
#include <FLTK/Help_View.h>


int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(700,680);

 // Input - wprowadzanie tekstu
   Fl_Input *inp1 = new Fl_Input(290,10,140,100,"Hello, World!");

  // output - wyœwietla tekst z value();
  Fl_Output *inp2 = new Fl_Output(290,115,140,100,"Hello, World!");

  // Fl_Multiline_Input - wielowierszowe wprowadzanie tekstu
  Fl_Multiline_Input *inp3 = new Fl_Multiline_Input(290,225,140,100,"Hello, World!");

  // Fl_Multiline_Input - wielowierszowe wyœwietlanie tekstu
  Fl_Multiline_Output *inp4 = new Fl_Multiline_Output(290,330,140,100,"Hello, World!");
 inp4->value("aaaaa*N*sssss*N*ssss");

   // Text Display - wyœwietla tekst z bajerami
  Fl_Text_Display *inp5 = new Fl_Text_Display(290,440,140,100,"Hello, World!");

   // Text Editor - edytuje tekst z bajerami
  Fl_Text_Editor *inp6 = new Fl_Text_Editor(290,550,140,100,"Hello, World!");

// wyœwietla tekst, parsuje podstawowe tagi HTML
  Fl_Help_View *inp7 = new Fl_Help_View(490,30,140,100,"Hello, World!");
   inp7->value("<B>Bold</B><BR>Nowa <I>linia</I>");

  window->end();
  window->show(argc, argv);
  return Fl::run();
}
