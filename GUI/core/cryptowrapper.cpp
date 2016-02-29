#include "GUI/core/cryptowrapper.h"
#include <crypto/aes_crypto.h>
#include <crypto/base64_crypto.h>

CryptoWrapper::CryptoWrapper(const QString& key, const QString& info)
        : m_key(key), m_info(info) {
    trim_info();
}

QString& CryptoWrapper::encrypt(QString &results) {
    crypto::Encryptor aes_cryptor(new crypto::Aes(m_key.toStdString()));
    crypto::Encryptor base64_cryptor(new crypto::Base64());
    std::string output, input(m_info.toStdString());

    aes_cryptor.encrypt(output, input.c_str(), input.size());
    base64_cryptor.encrypt(output, output.c_str(), output.size());

    results = QString::fromStdString(output);
    return results;
}

QString& CryptoWrapper::decrypt(QString &results) {
    crypto::Encryptor aes_cryptor(new crypto::Aes(m_key.toStdString()));
    crypto::Encryptor base64_cryptor(new crypto::Base64());
    std::string output, input(m_info.toStdString());

    base64_cryptor.decrypt(output, input.c_str(), input.size());
    aes_cryptor.decrypt(output, output.c_str(), output.size());

    results = QString::fromStdString(output);
    return results;
}

void CryptoWrapper::trim_info() {
    m_info = m_info.trimmed();
}
