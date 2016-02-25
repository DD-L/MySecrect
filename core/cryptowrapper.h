#ifndef QT_CRYPTOWRAPPER_H_1
#define QT_CRYPTOWRAPPER_H_1

#include <QString>

/**
 * @brief The CryptoWrapper class
 */
class CryptoWrapper {
public:
    /**
     * @brief CryptoWrapper constructor
     * @param key
     * @param info
     */
    CryptoWrapper(const QString& key, const QString& info);

    /**
     * @brief ~CryptoWrapper
     */
    virtual ~CryptoWrapper() {}

    /**
     * @brief Encrypt
     * @param results
     * @return results
     */
    QString& encrypt(QString& results);

    /**
     * @brief Decrypt
     * @param results
     * @return results
     */
    QString& decrypt(QString& results);
private:
    /**
     * @brief trim_info
     */
    void trim_info();
private:
    QString m_key;
    QString m_info;
}; // class CryptoWrapper

#endif // QT_CRYPTOWRAPPER_H_1
