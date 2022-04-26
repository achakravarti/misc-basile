// // file fltk-mini-edit.cc
// SPDX-License-Identifier: GPL-3.0-or-later

// A simple text editor program for the Fast Light Tool Kit (FLTK).
//
// This program is described in Chapter 4 of the FLTK Programmer's Guide.
//
// Copyright 1998-2022 by Bill Spitzak and Basile Starynkevitch and CEA



// Include necessary headers...
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

#include <string>

#include <FL/Fl.H>
#include <FL/platform.H> // for fl_open_callback
#include <FL/Fl_Group.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/filename.H>

// Custom class to demonstrate a specialized text editor
class MyEditor : public Fl_Text_Editor
{

  Fl_Text_Buffer *tbuff;      // text buffer
public:
  MyEditor(int X,int Y,int W,int H)
    : Fl_Text_Editor(X,Y,W,H), tbuff(nullptr)
  {
    tbuff = new Fl_Text_Buffer();    // text buffer
    buffer(tbuff);
  };
  void text(const char* val)
  {
    tbuff->text(val);
  };
  enum my_style_en
  {
    Style_Plain,
    Style_Voyel,
    Style_Letter,
    Style_Digit,
    Style_Unicode,
    Style__LAST
  };
  static constexpr Fl_Text_Editor::Style_Table_Entry style_table[(unsigned)Style__LAST] =
  {
    // FONT COLOR      FONT FACE           SIZE  ATTRIBUTE      BACKGROUND COLOR
    // --------------- --------------      ----  ---------      -----------------
    {  FL_BLACK,       FL_COURIER,         14,   0,             FL_WHITE }, //:Style_Plain,
    {  FL_DARK_GREEN,  FL_COURIER_BOLD,    14,   0,             FL_WHITE }, //:Style_Voyel,
    {  FL_DARK_BLUE,   FL_COURIER,         14,   0,             FL_WHITE }, //:Style_Letter,
    {  FL_CYAN,        FL_COURIER,         14,   0,             FL_WHITE }, //:Style_Digit,
    {  FL_DARK_RED,    FL_HELVETICA_BOLD,  14,   ATTR_BGCOLOR,  FL_GRAY0 }, //:Style_Unicode,
  };
  void decorate(void);
};				// end MyEditor

void
MyEditor::decorate(void)
{
  Fl_Text_Buffer*buf = buffer();
  assert (buf != nullptr);
  int curix= -1, previx= -1;
  int buflen = buf->length();
  for (curix=0;
       curix>=0 && curix<buflen;
       curix=buf->next_char(curix))
    {
      if (previx == curix)
        break;
      unsigned int curch = buf->char_at(curix);
      assert (curch>0);
      previx= curix;
    };
#warning incomplete MyEditor::decorate
} // end MyEditor::decorate


int
main(int argc, char **argv)
{
  std::string tistr = __FILE__;
  tistr.erase(sizeof(__FILE__)-4,3);
#ifdef GITID
  tistr += "/" GITID;
#endif
  Fl_Window *win = new Fl_Window(720, 480, tistr.c_str());
  MyEditor  *med = new MyEditor(10,10,win->w()-20,win->h()-20);
  med->text("Test\n"
            "Other\n"
            "0123456789\n"
            "°§ +\n");
  med->decorate();
  win->resizable(med);
  win->show();
  return Fl::run();
}  // end main

/****************
 **                           for Emacs...
 ** Local Variables: ;;
 ** compile-command: "./mini-edit-build.sh" ;;
 ** End: ;;
 ****************/