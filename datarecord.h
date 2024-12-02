#ifndef DATARECORD_H
#define DATARECORD_H

#include <QString>
#include <QDate>
#include <QVector>

// 地区名称列表，使用 QVector<QString> 存储所有地区
static const QVector<QString> regionNames = {
    "北京", "上海", "天津", "重庆",  // 直辖市
    "河北", "山西", "辽宁", "吉林", "黑龙江", // 华北和东北
    "江苏", "浙江", "安徽", "福建", "江西", "山东", // 华东
    "河南", "湖北", "湖南", "广东", "广西", "海南", // 中南
    "四川", "贵州", "云南", "西藏", // 西南
    "陕西", "甘肃", "青海", "宁夏", "新疆", // 西北
    "香港", "澳门", "台湾", // 港澳台
    "全国" // 全国
};

// 指标类型枚举
enum class indicatorType {
    fixedPhoneUsers,        // 固定电话用户数
    mobilePhoneUsers,       // 移动电话用户数
    internetUsers,          // 互联网用户数
    fixedAssetsInvestment,  // 通信固定资产投入
    communicationIncome,    // 通信业收入
    infoServiceIncome,      // 信息服务收入
    infoProductIncome       // 信息产品收入
};

// 存储计量单位的类
class ValueWithUnit {
public:
    ValueWithUnit() = default;
    ValueWithUnit(double value, const QString& unit) : m_value(value), m_unit(unit) {}

    double getValue() const { return m_value; }
    QString getUnit() const { return m_unit; }

    void setValue(double value) { m_value = value; }
    void setUnit(const QString& unit) { m_unit = unit; }

private:
    double m_value;
    QString m_unit;
};

// 用于存储数据记录的类
class dataRecord {
public:
    // 构造函数
    dataRecord() = default;
    dataRecord(
        const QString& regionName,  // 传入地区名称（QString）
        int year,                   // 年份
        const ValueWithUnit& fixedPhoneUsers, // 固定电话用户数及其单位
        const ValueWithUnit& mobilePhoneUsers, // 移动电话用户数及其单位
        const ValueWithUnit& internetUsers, // 互联网用户数及其单位
        const ValueWithUnit& fixedAssetsInvestment, // 通信固定资产投入及其单位
        const ValueWithUnit& communicationIncome, // 通信业收入及其单位
        const ValueWithUnit& infoServiceIncome, // 信息服务收入及其单位
        const ValueWithUnit& infoProductIncome // 信息产品收入及其单位
    );

    // 访问方法
    QString getRegion() const { return m_region; }  // 返回地区名称（QString）
    int getYear() const { return m_year; }
    ValueWithUnit getFixedPhoneUsers() const { return m_fixedPhoneUsers; }
    ValueWithUnit getMobilePhoneUsers() const { return m_mobilePhoneUsers; }
    ValueWithUnit getInternetUsers() const { return m_internetUsers; }
    ValueWithUnit getFixedAssetsInvestment() const { return m_fixedAssetsInvestment; }
    ValueWithUnit getCommunicationIncome() const { return m_communicationIncome; }
    ValueWithUnit getInfoServiceIncome() const { return m_infoServiceIncome; }
    ValueWithUnit getInfoProductIncome() const { return m_infoProductIncome; }

    // 设置方法
    void setRegion(const QString& regionName) { m_region = regionName; }
    void setYear(int year) { m_year = year; }
    void setFixedPhoneUsers(const ValueWithUnit& value) { m_fixedPhoneUsers = value; }
    void setMobilePhoneUsers(const ValueWithUnit& value) { m_mobilePhoneUsers = value; }
    void setInternetUsers(const ValueWithUnit& value) { m_internetUsers = value; }
    void setFixedAssetsInvestment(const ValueWithUnit& value) { m_fixedAssetsInvestment = value; }
    void setCommunicationIncome(const ValueWithUnit& value) { m_communicationIncome = value; }
    void setInfoServiceIncome(const ValueWithUnit& value) { m_infoServiceIncome = value; }
    void setInfoProductIncome(const ValueWithUnit& value) { m_infoProductIncome = value; }

private:
    QString m_region;            // 地区名称（QString）
    int m_year;                  // 年份
    ValueWithUnit m_fixedPhoneUsers;   // 固定电话用户数
    ValueWithUnit m_mobilePhoneUsers;  // 移动电话用户数
    ValueWithUnit m_internetUsers;     // 互联网用户数
    ValueWithUnit m_fixedAssetsInvestment; // 通信固定资产投入
    ValueWithUnit m_communicationIncome; // 通信业收入
    ValueWithUnit m_infoServiceIncome;  // 信息服务收入
    ValueWithUnit m_infoProductIncome; // 信息产品收入
};

#endif // DATARECORD_H
