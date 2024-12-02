#include "datarecord.h"

// dataRecord 构造函数的实现
dataRecord::dataRecord(
    const QString& regionName,  // 传入地区名称（QString）
    int year,                   // 年份
    const ValueWithUnit& fixedPhone,  // 固定电话用户数
    const ValueWithUnit& mobilePhone, // 移动电话用户数
    const ValueWithUnit& internet,    // 互联网用户数
    const ValueWithUnit& fixedAssets, // 通信固定资产投入
    const ValueWithUnit& communication, // 通信业收入
    const ValueWithUnit& infoService,  // 信息服务收入
    const ValueWithUnit& infoProduct  // 信息产品收入
)
    : m_region(regionName)           // 初始化 m_region 为传入的地区名称
    , m_year(year)                   // 初始化年份
    , m_fixedPhoneUsers(fixedPhone)  // 初始化固定电话用户数
    , m_mobilePhoneUsers(mobilePhone) // 初始化移动电话用户数
    , m_internetUsers(internet)      // 初始化互联网用户数
    , m_fixedAssetsInvestment(fixedAssets) // 初始化通信固定资产投入
    , m_communicationIncome(communication) // 初始化通信业收入
    , m_infoServiceIncome(infoService) // 初始化信息服务收入
    , m_infoProductIncome(infoProduct) // 初始化信息产品收入
{
}

// 你可以继续定义 getter 和 setter 方法，这部分保持不变
