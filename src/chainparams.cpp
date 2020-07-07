// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <utilstrencodings.h>
#include <arith_uint256.h>

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "5G for a better future without Barry. 23/05/2020";
    const CScript genesisOutputScript = CScript() << ParseHex("0444b2ec08abfb7c8572976b03d125d4a107e0f70a7e8c4895b44bbf3471a2308b63c837eede0ae1fa47d6d9144fbdccee62015c5e510149dec3ba53918dc42158") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)

{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 260000;
        consensus.nFirstPoSBlock = 555;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 8388638;
        consensus.nBudgetPaymentsCycleBlocks = 16616;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockCycle = 43200;
        consensus.nSuperblockStartBlock = consensus.nSuperblockCycle;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("06397fc963cdb1326abf547080ab1c5b2ef30c1a32c9ebc9aeab5c81d9ea27b3");
        consensus.BIP65Height = consensus.nFirstPoSBlock;
        consensus.BIP66Height = consensus.nFirstPoSBlock;
        consensus.powLimit = uint256S("0000ffff00000000000000000000000000000000000000000000000000000000");
        consensus.posLimit = uint256S("007ffff000000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 2 * 60;
        consensus.nPowTargetSpacing = 60;
        consensus.nPosTargetSpacing = consensus.nPowTargetSpacing;
        consensus.nPosTargetTimespan = consensus.nPowTargetTimespan;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nStakeMinAge = 60 * 60 * 24 * 15; // 15 Days
        consensus.nStakeMaxAge = 60 * 60 * 24 * 90; // 90 Days
        consensus.nModifierInterval = 60 * 20;
        consensus.nCoinbaseMaturity = 20;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1080;
        consensus.nMinerConfirmationWindow = 1440;
        consensus.nMinStakeAmount = 50 * COIN;
        consensus.nMinStakeHistory = 10;
        consensus.nMnCheckChangeHeight = 62300;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1479168000; // November 15th, 2016.
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1510704000; // November 15th, 2017.

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("00000000000000000000000000000000000000000000000000119da393fbb525");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("ae4cf754778d83769cb9b8a7ddf5d2b233b090d1e9cda6050cbb9d10cf5e2701");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x35; // 5
        pchMessageStart[1] = 0x47; // G
        pchMessageStart[2] = 0x43; // C
        pchMessageStart[3] = 0x48; // H
        nDefaultPort = 34555;
        nPruneAfterHeight = 100000;
        nMaxReorganizationDepth = 100;

        genesis = CreateGenesisBlock(1556915433, 56542, 0x1f00ffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();


	// 5G addresses start with 'F'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
	// 5G script addresses start with 'v'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,132);
	// 5G private keys start with '2'
	base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,198);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};
        bech32_hrp = "fg";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        nCollateralLevels = { 10000, 20000, 30000 };
        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60;
        strSporkPubKey = "0360cde54d90fc012b41bc4b0fafd10727ad1559571d9438678a56b9f5e22cae63";
        strSporkPubAddr = "76a9141a2f7b671c54fcb175eaaf26d5a0b09e6620a35288ac";

        checkpointData = {
          {
            {
              0,
              uint256S("0x06397fc963cdb1326abf547080ab1c5b2ef30c1a32c9ebc9aeab5c81d9ea27b3")
            },

            {
              2000,
              uint256S("0x06dbf443ad728beb7344ec0bcb647d39015cbcc36bd5e684779e1cd4da5c5ab5")
            }, {
              4000,
              uint256S("0x670154a6e658d13ae9f63e216389e1b3a37957a5ba6c733b39c03f76a4fdb674")
            }, {
              6000,
              uint256S("0x07af6c91709918e11f7239eb7aa96a8b0c6a662f1540d570d790a2e81df05d7b")
            }, {
              8000,
              uint256S("0x8d060d95b5b257d62830fa71f30998de0aa6b5218b5c7f39ae6efb443a7c35b0")
            }, {
              10000,
              uint256S("0x67feed59e7d4ff189538c61bffb4c394c07f820d1955c2f3068dec2026ab3913")
            }, {
              12000,
              uint256S("0x70fbeadd10fdf9214e18259f8a0f838044d7c9cd7b6b62afd398b70710270cac")
            }, {
              14000,
              uint256S("0xaa0f0abcba3f52cb37deee2afcd317b25c04107515940e923d3c95b35213de76")
            }, {
              16000,
              uint256S("0x27d6c7dcecb514ede24d082de5373af2ee3ee79920129053ede90e842542f671")
            }, {
              18000,
              uint256S("0x0347401f3940297fe2aa9c3f4b1eade289211cbf43ae755e0ec41d0d25798ef1")
            }, {
              20000,
              uint256S("0x8a4326862d68d4082d8c70f07eaacac9e1e319180c656f7cac09cfe6ba12e2d3")
            }, {
              22000,
              uint256S("0x8058b9c10c9567618a5d4dcb9dbc6afc0901db66dd3bb83583088a6913489ef4")
            }, {
              24000,
              uint256S("0xa25357906a0378437926428ba88eae5c72ebd95142dd85e5f71d848da6139978")
            }, {
              26000,
              uint256S("0x9c2871a7c1b03717d5d11ee01e9447d017fdd103e41d0f1fb2b7265064e1c150")
            }, {
              28000,
              uint256S("0x15448f6aa0937e5043116f45892b86443f60dfc7c93ffd584afacfb6c04317ff")
            }, {
              30000,
              uint256S("0x899e3f93d47908810ba988110b345c669ae7b4eaa055c132a7c0445c7a5f8b99")
            }, {
              34000,
              uint256S("0xe2837f64ef85308755f19ca5eaf16c4603524b357c45fe72d5e0b48297c032c6")
            }, {
              34030,
              uint256S("0x36dd81dcbff9829781e8d19737b734c6e859a65aa95073440572bdd35c17ddb8")
            }
          }
        };

        chainTxData = ChainTxData {
          1592331757, // * UNIX timestamp of last checkpoint block
          35993, // * total number of transactions between genesis and last checkpoint
          //   (the tx=... number in the SetBestChain debug.log lines)
          2000 // * estimated number of transactions per day after checkpoint
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = true;
    }
};

/*
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 260000;
        consensus.nFirstPoSBlock = 50;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 8388638;
        consensus.nBudgetPaymentsCycleBlocks = 16616;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockCycle = 43200;
        consensus.nSuperblockStartBlock = consensus.nSuperblockCycle;
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("380717cf377350bd708b8d202270a3e389b03aba949daf4199fa468d57a01ad7");
        consensus.BIP65Height = consensus.nFirstPoSBlock;
        consensus.BIP66Height = consensus.nFirstPoSBlock;
        consensus.powLimit = uint256S("0000ffff00000000000000000000000000000000000000000000000000000000");
        consensus.posLimit = uint256S("007ffff000000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 2 * 60;
        consensus.nPowTargetSpacing = 60;
        consensus.nPosTargetSpacing = consensus.nPowTargetSpacing;
        consensus.nPosTargetTimespan = consensus.nPowTargetTimespan;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nStakeMinAge = 10 * 60; // 10 Minutes
        consensus.nStakeMaxAge = 60 * 60 * 24 * 90; // 90 Days
        consensus.nModifierInterval = 60 * 20;
        consensus.nCoinbaseMaturity = 20;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1080;
        consensus.nMinerConfirmationWindow = 1440;
        consensus.nMinStakeAmount = 1 * COIN;
        consensus.nMinStakeHistory = 10;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800; // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1479168000; // November 15th, 2016.
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1510704000; // November 15th, 2017.

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0000000000000000000000000000000000000000000000000000000001203f1e");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("90a7657cd65eb7089fa71705c69ccce238800fdbae3386f3fe3c42eedc3af330");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x65; // T
        pchMessageStart[1] = 0x33; // E
        pchMessageStart[2] = 0x63; // S
        pchMessageStart[3] = 0x65; // T
        nDefaultPort = 44551;
        nPruneAfterHeight = 100000;
        nMaxReorganizationDepth = 100;

        genesis = CreateGenesisBlock(1590243846, 52541, 0x1f00ffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

		// 5G addresses start with 'T'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
		// 5G script addresses start with 't'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,127);
		// 5G private keys start with '2'
		base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,218);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tf";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        nCollateralLevels = { 10000, 20000, 30000 };
        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60;
        
		strSporkPubKey = "0289e9283716834af4ad3cbfa582343c459a6761db4366c81f4987c36fa6d604c5";
       	strSporkPubAddr = "76a914c5e90f7c735c1017a2a00f9383ae07a3af525de288ac";

        checkpointData = {
 			{
				{0, uint256S("0xce071bc212ac756b52417fd4d26ea9bea569ff013e3b70f5a92711d810d611a4")},
                {60, uint256S("0xd66014a94b456b2f3c119b76ed3ad4b12766dbae3a3a0e6f97f0a535d1436af8")},
				{88, uint256S("0x41f55beb74f5a8f63721feb7677c89c416453150b46353d3448e8120ec0b7301")},
            }
			
        };

        chainTxData = ChainTxData{
 				1590262718,
        		106,
        		0.028
        };

        /* disable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/*
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
