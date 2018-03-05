#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H

#include <QByteArray>
#include <QString>

class CryptoUtils {
private:
    static const QByteArray salt;
    static QByteArray deriveKey(const QByteArray &passphrase);
    static QByteArray encrypt(const QByteArray &message, const QByteArray &key);
    static QByteArray decrypt(const QByteArray &message, const QByteArray &key);
    static QString baseHanziEncode(const QByteArray &message, const QString &base);
    static QByteArray baseHanziDecode(const QString &message, const QString &base);
public:
    static int init();
    static QString encrypt(const QByteArray &message, const QByteArray &passphrase, const QString &base);
    static QByteArray decrypt(const QString &message, const QByteArray &passphrase, const QString &base);
};

#endif // CRYPTOUTILS_H
