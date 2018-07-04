// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CHAINPARAMS_H
#define BITCOIN_CHAINPARAMS_H

#include "chainparamsbase.h"
#include "consensus/params.h"
#include "primitives/block.h"
#include "protocol.h"

#include <vector>

///////////////////////////
///   ALTCOIN SETTINGS  ///
///////////////////////////

static const int64_t SINGLE_BLOCK_REWARD = 50;
static const int64_t PREMINE_REWARD = 50000;
static const char* PSZ_TIMESTAMP = "July 5, 2018 Your roof is running away from you... x_0";
static const char* PUBLIC_KEY = "04b41de5b1633fbb8c3f08b8f2c8e109e2e95b6e6cc9f898c4f7033fc0d1e27f2f25ac909c301a3e4e4cf07eeaa01a8f1399577c2d0c350db4b4a61d40b7f3bd2b";
static const char* HASH_MERKLE_ROOT = "0x6720b98383eda318c6d24701523745707a159d94803689fd8489af592549fc3e";

// MAIN
static const MAIN_GENESIS = "0x0000090A5715078FDA105A67C0F111323AA1E28BDBFBB17A117DB8C7FC2DEA73";
static const int MAIN_TIMESTAMP = 1530687600;
static const int MAIN_NONCE = 405043;
static const int MAIN_BITS = 0x1e0ffff0;
static const int MAIN_VERSION = 1;
static const char* MAIN_ALERT_PUB_KEY = "04831983ff9f4b1ce1d940a4414fcc7ec6ee9da4bad48b3476ea504ecb873ca1b3d9132ed90b9a2b1c9fe4b38b6e5b274163d4f0b3f02f8a73e34d8c5aa3054370";
static const char* MAIN_SPORK_PUB_KEY = "043ea141133aec5be74be221ac9dad7f672ead28774ef38edeb464e6849ee4eb1ebfae4b543bd43ad9e3f7db186c63830a86faf96f7c8bdfdaadb298192743d349";

// TESTNET
static const TEST_GENESIS = "0x00000A3AD87192B0B84210E5E6136703538C65307EA9AE147752BA5549D8E3C1";
static const int TEST_TIMESTAMP = 1530687601;
static const int TEST_NONCE = 1438801;
static const int TEST_BITS = 0x1e0ffff0;
static const int TEST_VERSION = 1;
static const char* TEST_ALERT_PUB_KEY = "04fbb84ca0f71ae10ce9c80b1b5c0e806c5fcb99a0949e9abb8337d3341ea338de9a23babc2f2d555f077858f60179cfed1907d4563ce62d74768e7e3b367cec85";
static const char* TEST_SPORK_PUB_KEY = "04d7e900253a75a6e9ed831694dd5538f2791c334b5b2578f5c03904053c9a93737acd2b917afd9a93ea276a61a5fec16292553e1273765c358923c9d390fbd806";

// REGTESTNET
static const REGTEST_GENESIS = "0x000001A2E8CAE6E1686C9CEEA62802056ED2E6DE933916AF9CB4ACDD5FDEB0BA";
static const int REGTEST_TIMESTAMP = 1530687602;
static const int REGTEST_NONCE = 161592;
static const  int REGTEST_BITS = 0x1e0ffff0;
static const int REGTEST_VERSION = 1;
static const char* REGTEST_ALERT_PUB_KEY = "04831983ff9f4b1ce1d940a4414fcc7ec6ee9da4bad48b3476ea504ecb873ca1b3d9132ed90b9a2b1c9fe4b38b6e5b274163d4f0b3f02f8a73e34d8c5aa3054370";
static const char* REGTEST_SPORK_PUB_KEY = "043ea141133aec5be74be221ac9dad7f672ead28774ef38edeb464e6849ee4eb1ebfae4b543bd43ad9e3f7db186c63830a86faf96f7c8bdfdaadb298192743d349";

//////////////////////////////////
///  END OF ALTCOIN SETTINGS  ///
/////////////////////////////////

struct CDNSSeedData {
    std::string name, host;
    CDNSSeedData(const std::string &strName, const std::string &strHost) : name(strName), host(strHost) {}
};

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

typedef std::map<int, uint256> MapCheckpoints;

struct CCheckpointData {
    MapCheckpoints mapCheckpoints;
    int64_t nTimeLastCheckpoint;
    int64_t nTransactionsLastCheckpoint;
    double fTransactionsPerDay;
};

/**
 * CChainParams defines various tweakable parameters of a given instance of the
 * Dash system. There are three: the main network on which people trade goods
 * and services, the public test network which gets reset from time to time and
 * a regression test mode which is intended for private networks only. It has
 * minimal difficulty to ensure that blocks can be found instantly.
 */
class CChainParams
{
public:
    enum Base58Type {
        PUBKEY_ADDRESS,
        SCRIPT_ADDRESS,
        SECRET_KEY,     // BIP16
        EXT_PUBLIC_KEY, // BIP32
        EXT_SECRET_KEY, // BIP32

        MAX_BASE58_TYPES
    };

    const Consensus::Params& GetConsensus() const { return consensus; }
    const CMessageHeader::MessageStartChars& MessageStart() const { return pchMessageStart; }
    const std::vector<unsigned char>& AlertKey() const { return vAlertPubKey; }
    int GetDefaultPort() const { return nDefaultPort; }

    const CBlock& GenesisBlock() const { return genesis; }
    /** Make miner wait to have peers to avoid wasting work */
    bool MiningRequiresPeers() const { return fMiningRequiresPeers; }
    /** Default value for -checkmempool and -checkblockindex argument */
    bool DefaultConsistencyChecks() const { return fDefaultConsistencyChecks; }
    /** Policy: Filter transactions that do not match well-defined patterns */
    bool RequireStandard() const { return fRequireStandard; }
    int64_t MaxTipAge() const { return nMaxTipAge; }
    int64_t DelayGetHeadersTime() const { return nDelayGetHeadersTime; }
    uint64_t PruneAfterHeight() const { return nPruneAfterHeight; }
    /** Make miner stop after a block is found. In RPC, don't return until nGenProcLimit blocks are generated */
    bool MineBlocksOnDemand() const { return fMineBlocksOnDemand; }
    /** In the future use NetworkIDString() for RPC fields */
    bool TestnetToBeDeprecatedFieldRPC() const { return fTestnetToBeDeprecatedFieldRPC; }
    /** Return the BIP70 network string (main, test or regtest) */
    std::string NetworkIDString() const { return strNetworkID; }
    const std::vector<CDNSSeedData>& DNSSeeds() const { return vSeeds; }
    const std::vector<unsigned char>& Base58Prefix(Base58Type type) const { return base58Prefixes[type]; }
    int ExtCoinType() const { return nExtCoinType; }
    const std::vector<SeedSpec6>& FixedSeeds() const { return vFixedSeeds; }
    const CCheckpointData& Checkpoints() const { return checkpointData; }
    int PoolMaxTransactions() const { return nPoolMaxTransactions; }
    int FulfilledRequestExpireTime() const { return nFulfilledRequestExpireTime; }
    std::string SporkPubKey() const { return strSporkPubKey; }
protected:
    CChainParams() {}

    Consensus::Params consensus;
    CMessageHeader::MessageStartChars pchMessageStart;
    //! Raw pub key bytes for the broadcast alert signing key.
    std::vector<unsigned char> vAlertPubKey;
    int nDefaultPort;
    long nMaxTipAge;
    int64_t nDelayGetHeadersTime;
    uint64_t nPruneAfterHeight;
    std::vector<CDNSSeedData> vSeeds;
    std::vector<unsigned char> base58Prefixes[MAX_BASE58_TYPES];
    int nExtCoinType;
    std::string strNetworkID;
    CBlock genesis;
    std::vector<SeedSpec6> vFixedSeeds;
    bool fMiningRequiresPeers;
    bool fDefaultConsistencyChecks;
    bool fRequireStandard;
    bool fMineBlocksOnDemand;
    bool fTestnetToBeDeprecatedFieldRPC;
    CCheckpointData checkpointData;
    int nPoolMaxTransactions;
    int nFulfilledRequestExpireTime;
    std::string strSporkPubKey;
    std::string strMasternodePaymentsPubKey;
};

/**
 * Return the currently selected parameters. This won't change after app
 * startup, except for unit tests.
 */
const CChainParams &Params();

/**
 * @returns CChainParams for the given BIP70 chain name.
 */
CChainParams& Params(const std::string& chain);

/**
 * Sets the params returned by Params() to those for the given BIP70 chain name.
 * @throws std::runtime_error when the chain is not supported.
 */
void SelectParams(const std::string& chain);

#endif // BITCOIN_CHAINPARAMS_H
