// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

#define SHOW_LOG true

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x8c;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0x5a;
        pchMessageStart[3] = 0xd3;
        vAlertPubKey = ParseHex("0485ac8fc2147631e512c7f4e8c90333910e8ebad7b757366de376a1ad7ea66e11b58cce91cb881720dc9ce20e9f6057dbdc6d7f7dfe74658de8234465d19d43f1");
        nDefaultPort = 78037;
        nRPCPort = 78036;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

            const char* pszTimestamp = "April Fool's Day 2018: How the EU trolled Britain";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1523995200, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1523995200;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 55382;

        hashGenesisBlock = genesis.GetHash();
#ifdef SHOW_LOG
        //printf("genesis.hashGenesisBlock == %s\n", hashGenesisBlock.ToString().c_str());
        //printf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("genesis.nBits == %d\n", genesis.nBits);
        //printf("genesis.nNonce == %d\n", genesis.nNonce);
        LogPrintf("genesis.hashGenesisBlock == %s\n", hashGenesisBlock.ToString().c_str());
        LogPrintf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("genesis.nBits == %d\n", genesis.nBits);
        LogPrintf("genesis.nNonce == %d\n", genesis.nNonce);
#endif
        assert(hashGenesisBlock == uint256("063499918eec5efad8464fd5643b2844429efa7cb3240a2dc1f39645c564b69c"));
        assert(genesis.hashMerkleRoot == uint256("a7cb4c3a69db0dbc49e0964133af2b1898abd9316eaaa1b72636f197578a1d9f"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,70);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,30);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,140);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("1","140.82.34.146"));   
        vSeeds.push_back(CDNSSeedData("2","207.148.117.114"));     
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;

        strDarksendPoolDummyAddress = "";
        nLastPOWBlock = 200000;
        nPOSStartBlock = 3333;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc3;
        pchMessageStart[1] = 0xdf;
        pchMessageStart[2] = 0xb8;
        pchMessageStart[3] = 0x5f;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04a5da3e2f20d1e8b49b9b675b69f2a27f62b65af88108cb02135df9f5b5a83cfda167f64867582cc79e2e899c157c7a71f2d23f74e83089f4ed9e093f3dc23ea0");
        nDefaultPort = 78837;
        nRPCPort = 78836;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1523995200;
        genesis.nNonce = 44;
#ifdef SHOW_LOG
        LogPrintf("CTestNetParams.hashGenesisBlock == %s\n", hashGenesisBlock.ToString().c_str());
        LogPrintf("CTestNetParams.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("CTestNetParams.nBits == %d\n", genesis.nBits);
        LogPrintf("CTestNetParams.nNonce == %d\n", genesis.nNonce);
#endif
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,27);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
