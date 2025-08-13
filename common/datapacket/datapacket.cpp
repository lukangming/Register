#include "datapacket.h"

sDataPacket::sDataPacket()
{
    dev = new sDevData;
    pro = new sProgress();
}

sDataPacket *sDataPacket::build()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}

void sDataPacket::init()
{
    // pro->step = 0;
    // pro->result = 0;
    // pro->pass.clear();
    // pro->status.clear();

    dev->dt.user = "";
    dev->dt.keylength = "";
    dev->dt.paddingMode = "";
    dev->dt.paddingMode = "";
    dev->dt.iv = "";
    dev->dt.key = "";
    dev->dt.customer = "";
    dev->dt.activationCode = "";
    dev->dt.sn = "";
    dev->dt.licenseFile = "";

    // pro->result = Test_Info;
    // pro->startTime = QTime::currentTime();
}
