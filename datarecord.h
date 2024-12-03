#ifndef DATARECORD_H
#define DATARECORD_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QJsonObject>  // 添加头文件用于 JSON 转换

static const QVector<QString> regionNames = {
    "北京", "上海", "天津", "重庆",
    "河北", "山西", "辽宁", "吉林", "黑龙江",
    "江苏", "浙江", "安徽", "福建", "江西", "山东",
    "河南", "湖北", "湖南", "广东", "广西", "海南",
    "四川", "贵州", "云南", "西藏",
    "陕西", "甘肃", "青海", "宁夏", "新疆",
    "香港", "澳门", "台湾",
    "全国"
};

enum class indicatorType {
    fixedPhoneUsers,
    mobilePhoneUsers,
    internetUsers,
    fixedAssetsInvestment,
    communicationIncome,
    infoServiceIncome,
    infoProductIncome
};

// ValueWithUnit 类转换为 QJsonObject
class ValueWithUnit {
public:
    ValueWithUnit() = default;
    ValueWithUnit(double value, const QString& unit) : m_value(value), m_unit(unit) {}

    double getValue() const { return m_value; }
    QString getUnit() const { return m_unit; }

    void setValue(double value) { m_value = value; }
    void setUnit(const QString& unit) { m_unit = unit; }

    // 转换为 QJsonObject
    QJsonObject toJson() const {
        QJsonObject json;
        json["value"] = m_value;
        json["unit"] = m_unit;
        return json;
    }

private:
    double m_value;
    QString m_unit;
};

// dataRecord 类转换为 QJsonObject
class dataRecord {
public:
    dataRecord() = default;
    dataRecord(
        const QString& regionName,
        int year,
        const ValueWithUnit& fixedPhoneUsers,
        const ValueWithUnit& mobilePhoneUsers,
        const ValueWithUnit& internetUsers,
        const ValueWithUnit& fixedAssetsInvestment,
        const ValueWithUnit& communicationIncome,
        const ValueWithUnit& infoServiceIncome,
        const ValueWithUnit& infoProductIncome
        );

    QString getRegion() const { return m_region; }
    int getYear() const { return m_year; }
    ValueWithUnit getFixedPhoneUsers() const { return m_fixedPhoneUsers; }
    ValueWithUnit getMobilePhoneUsers() const { return m_mobilePhoneUsers; }
    ValueWithUnit getInternetUsers() const { return m_internetUsers; }
    ValueWithUnit getFixedAssetsInvestment() const { return m_fixedAssetsInvestment; }
    ValueWithUnit getCommunicationIncome() const { return m_communicationIncome; }
    ValueWithUnit getInfoServiceIncome() const { return m_infoServiceIncome; }
    ValueWithUnit getInfoProductIncome() const { return m_infoProductIncome; }

    void setRegion(const QString& regionName) { m_region = regionName; }
    void setYear(int year) { m_year = year; }
    void setFixedPhoneUsers(const ValueWithUnit& value) { m_fixedPhoneUsers = value; }
    void setMobilePhoneUsers(const ValueWithUnit& value) { m_mobilePhoneUsers = value; }
    void setInternetUsers(const ValueWithUnit& value) { m_internetUsers = value; }
    void setFixedAssetsInvestment(const ValueWithUnit& value) { m_fixedAssetsInvestment = value; }
    void setCommunicationIncome(const ValueWithUnit& value) { m_communicationIncome = value; }
    void setInfoServiceIncome(const ValueWithUnit& value) { m_infoServiceIncome = value; }
    void setInfoProductIncome(const ValueWithUnit& value) { m_infoProductIncome = value; }

    // 转换为 QJsonObject
    QJsonObject toJson() const {
        QJsonObject json;
        json["region"] = m_region;
        json["year"] = m_year;
        json["fixedPhoneUsers"] = m_fixedPhoneUsers.toJson();
        json["mobilePhoneUsers"] = m_mobilePhoneUsers.toJson();
        json["internetUsers"] = m_internetUsers.toJson();
        json["fixedAssetsInvestment"] = m_fixedAssetsInvestment.toJson();
        json["communicationIncome"] = m_communicationIncome.toJson();
        json["infoServiceIncome"] = m_infoServiceIncome.toJson();
        json["infoProductIncome"] = m_infoProductIncome.toJson();
        return json;
    }

private:
    QString m_region;
    int m_year;
    ValueWithUnit m_fixedPhoneUsers;
    ValueWithUnit m_mobilePhoneUsers;
    ValueWithUnit m_internetUsers;
    ValueWithUnit m_fixedAssetsInvestment;
    ValueWithUnit m_communicationIncome;
    ValueWithUnit m_infoServiceIncome;
    ValueWithUnit m_infoProductIncome;
};

#endif // DATARECORD_H

