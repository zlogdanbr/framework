#ifndef CUI_H
#define CUI_H


#include <gtk/gtk.h>

class cui
{
public:
    cui();
    virtual ~cui();
    void initApp();
protected:
private:
    // Disable copy constructor e operador atribuicao
    cui(const cui& other);
    cui& operator=(const cui& other);

    // GUI components
    GtkWidget *window;
    GtkWidget *label1, *label2, *label3;
    GtkWidget *hbox;
    GtkWidget *vbox;

    //Events
    static void destroy();
};

#endif // CUI_H
