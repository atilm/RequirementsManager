#include "htmltemplatefactory.h"
#include "qfileadapter.h"
#include "qtextstreamadapter.h"

HtmlTemplateFactory::HtmlTemplateFactory()
{
}

HtmlTemplate *HtmlTemplateFactory::newTemplate()
{
    return new HtmlTemplate(new QFileAdapter(), new QTextStreamAdapter());
}
