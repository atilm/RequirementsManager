#ifndef HTMLTEMPLATEFACTORY_H
#define HTMLTEMPLATEFACTORY_H

#include "htmltemplate.h"

class HtmlTemplateFactory
{
public:
    HtmlTemplateFactory();
    virtual ~HtmlTemplateFactory();

    virtual HtmlTemplate* newTemplate();
};

#endif // HTMLTEMPLATEFACTORY_H
