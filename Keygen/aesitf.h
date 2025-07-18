#ifndef AESITF_H
#define AESITF_H

#include <QByteArray>
#include "qaesencryption.h"

struct sAesItf
{
    QAESEncryption::Aes level;       // AES密钥长度
    QAESEncryption::Mode mode;       // 加密模式
    QAESEncryption::Padding padding; // 填充方式
    QByteArray key;                  // 密钥
    QByteArray iv;                   // 偏移量

    sAesItf()
        : level(QAESEncryption::AES_128)
        , mode(QAESEncryption::ECB)
        , padding(QAESEncryption::PKCS7)  // PKCS7
    {
        key = QByteArray::fromHex("00112233445566778899aabbccddeeff");
        iv  = QByteArray::fromHex("");
    }
};


#endif // AESITF_H


