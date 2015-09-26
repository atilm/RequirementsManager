#include "projectfilereader.h"

ProjectFileReader::ProjectFileReader(QXmlStreamReader *xml)
{
    this->xml = xml;
}

ProjectFileReader::~ProjectFileReader()
{
    delete xml;
}

void ProjectFileReader::load(RequirementsModel *model, QFileAdapter *file)
{

}
