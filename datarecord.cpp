#include "datarecord.h"

dataRecord::dataRecord(
    region reg,
    int yr,
    indicatorType ind,
    const QString& un,
    double val)
    : m_region(reg)
    , m_year(yr)
    , m_indicatorType(ind)
    , m_unit(un)
    , m_value(val)
{
}