#include "projectfilewriter.h"

ProjectFileWriter::ProjectFileWriter(QXmlStreamWriter *xml)
{
    this->xml = xml;
}

ProjectFileWriter::~ProjectFileWriter()
{
    delete xml;
}

void ProjectFileWriter::save(RequirementsModel *model,
                             QFileAdapter *file)
{

}
