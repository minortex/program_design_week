#ifndef DATARECORD_H
#define DATARECORD_H

#include <QString>
#include <QDate>

// 地区枚举
enum class region {
    Beijing, Shanghai, Tianjin, Chongqing,  // 直辖市
    Hebei, Shanxi, Liaoning, Jilin, Heilongjiang, // 华北和东北
    Jiangsu, Zhejiang, Anhui, Fujian, Jiangxi, Shandong, // 华东
    Henan, Hubei, Hunan, Guangdong, Guangxi, Hainan, // 中南
    Sichuan, Guizhou, Yunnan, Tibet, // 西南
    Shaanxi, Gansu, Qinghai, Ningxia, Xinjiang, // 西北
    HongKong, Macao, Taiwan, // 港澳台
    National // 全国
};

// 指标类型枚举
enum class indicatorType {
    fixedPhoneUsers,        // 固定电话用户数
    mobilePhoneUsers,       // 移动电话用户数
    internetUsers,          // 互联网用户数
    fixedAssetsInvestment, // 通信固定资产投入
    communicationIncome,    // 通信业收入
    infoServiceIncome,      // 信息服务收入
    infoProductIncome       // 信息产品收入
};

class dataRecord {
public:
    // 构造函数
    dataRecord() = default;
    dataRecord(             // 构造函数名称
        region region,      // 参数1：地区枚举类型
        int year,          // 参数2：年份
        indicatorType indicator, // 参数3：指标类型枚举
        const QString& unit,    // 参数4：计量单位（字符串引用）
        double value      // 参数5：数值
    );

    // 访问方法
    region getRegion() const { return m_region; }
    int getYear() const { return m_year; }
    indicatorType getIndicatorType() const { return m_indicatorType; }
    QString getUnit() const { return m_unit; }
    double getValue() const { return m_value; }

    // 设置方法
    void setRegion(region region){ m_region = region; }
    void setYear(int year) { m_year = year; }
    void setIndicatorType(indicatorType type) { m_indicatorType = type; }
    void setUnit(const QString& unit) { m_unit = unit; }
    void setValue(double value) { m_value = value; }

private:
    region m_region;            // 地区
    int m_year;                 // 年份
    indicatorType m_indicatorType; // 指标名称
    QString m_unit;             // 计量单位
    double m_value;             // 指标数量
};

#endif // DATARECORD_H

