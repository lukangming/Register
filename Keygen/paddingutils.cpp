#include "PaddingUtils.h"

namespace PaddingUtils {

QByteArray removePKCS7Padding(const QByteArray &data)
{
    if (data.isEmpty()) return data;
    unsigned char pad = static_cast<unsigned char>(data.at(data.size() - 1));
    if (pad == 0 || pad > 16) return data;
    for (int i = 0; i < pad; ++i) {
        if (static_cast<unsigned char>(data.at(data.size() - 1 - i)) != pad) {
            return data;
        }
    }
    return data.left(data.size() - pad);
}

QByteArray removeISO7816Padding(const QByteArray &data)
{
    int i = data.size() - 1;
    while (i >= 0 && data.at(i) == '\x00') {
        --i;
    }
    if (i >= 0 && data.at(i) == '\x80') {
        return data.left(i);
    }
    return data; // 未检测到填充标志，返回原文
}

QByteArray removeZeroPadding(const QByteArray &data)
{
    int i = data.size();
    while (i > 0 && data.at(i - 1) == '\x00') {
        --i;
    }
    return data.left(i);
}

} // namespace PaddingUtils
