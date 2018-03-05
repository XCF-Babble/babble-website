#include "cryptoutils.h"
#include <sodium.h>

const QByteArray CryptoUtils::salt("BabbleBabbleBabb");

QByteArray CryptoUtils::deriveKey(const QByteArray &passphrase) {
    QByteArray ret(crypto_aead_chacha20poly1305_IETF_KEYBYTES, 0);
    if (crypto_pwhash((unsigned char*) ret.data(), ret.length(),
                      passphrase.data(), passphrase.length(),
                      (unsigned char*) salt.data(),
                      crypto_pwhash_OPSLIMIT_INTERACTIVE,
                      crypto_pwhash_MEMLIMIT_INTERACTIVE,
                      crypto_pwhash_ALG_DEFAULT) != 0) {
        return QByteArray();
    }
    return ret;
}

QByteArray CryptoUtils::encrypt(const QByteArray &message, const QByteArray &key) {
    if (key.length() != crypto_aead_chacha20poly1305_IETF_KEYBYTES) {
        return QByteArray();
    }
    QByteArray nonce(crypto_aead_chacha20poly1305_IETF_NPUBBYTES, 0);
    QByteArray ret(message.length() + crypto_aead_chacha20poly1305_IETF_ABYTES, 0);
    unsigned long long len;
    randombytes_buf(nonce.data(), nonce.length());
    crypto_aead_chacha20poly1305_ietf_encrypt((unsigned char*) ret.data(), &len,
                                              (unsigned char*) message.data(), message.length(),
                                              NULL, 0, NULL,
                                              (unsigned char*) nonce.data(),
                                              (unsigned char*) key.data());
    ret.resize(len);
    return nonce + ret;
}

QByteArray CryptoUtils::decrypt(const QByteArray &message, const QByteArray &key) {
    if (key.length() != crypto_aead_chacha20poly1305_IETF_KEYBYTES
        || (unsigned int) message.length() < crypto_aead_chacha20poly1305_IETF_NPUBBYTES
                                           + crypto_aead_chacha20poly1305_IETF_ABYTES) {
        return QByteArray();
    }
    QByteArray nonce(message.left(crypto_aead_chacha20poly1305_IETF_NPUBBYTES));
    QByteArray cipher(message.right(message.length() - crypto_aead_chacha20poly1305_IETF_NPUBBYTES));
    QByteArray ret(cipher.length() - crypto_aead_chacha20poly1305_IETF_ABYTES, 0);
    unsigned long long len;
    if (crypto_aead_chacha20poly1305_ietf_decrypt((unsigned char*) ret.data(), &len,
                                                  NULL,
                                                  (unsigned char*) cipher.data(), cipher.length(),
                                                  NULL, 0,
                                                  (unsigned char*) nonce.data(),
                                                  (unsigned char*) key.data())) {
        return QByteArray();
    }
    ret.resize(len);
    return ret;
}

QString CryptoUtils::baseHanziEncode(const QByteArray &message, const QString &base) {
    if (base.length() != 256) {
        return QString();
    }
    QString ret;
    for (int i = 0; i < message.length(); ++i) {
        ret.append(base[(unsigned char) message[i]]);
    }
    return ret;
}

QByteArray CryptoUtils::baseHanziDecode(const QString &message, const QString &base) {
    if (base.length() != 256) {
        return QByteArray();
    }
    QByteArray ret;
    for (int i = 0; i < message.length(); ++i) {
        int index = base.indexOf(message[i]);
        if (index != -1) {
            ret.append(index);
        }
    }
    return ret;
}

int CryptoUtils::init() {
    return sodium_init();
}

QString CryptoUtils::encrypt(const QByteArray &message, const QByteArray &passphrase, const QString &base) {
    return baseHanziEncode(encrypt(message, deriveKey(passphrase)), base);
}

QByteArray CryptoUtils::decrypt(const QString &message, const QByteArray &passphrase, const QString &base) {
    return decrypt(baseHanziDecode(message, base), deriveKey(passphrase));
}
