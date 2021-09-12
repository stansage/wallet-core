// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.
//
// This is a GENERATED FILE, changes made here MAY BE LOST.
// Generated one-time (codegen/bin/cointests)
//

#include "../interface/TWTestUtilities.h"
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <gtest/gtest.h>


TEST(TWWestendCoinType, TWCoinType) {
    auto symbol = WRAPS(TWCoinTypeConfigurationGetSymbol(TWCoinTypeWestend));
    auto txId = WRAPS(TWStringCreateWithUTF8Bytes("0xb53b5362b18c7458737b8133ac80fa36b1b159ac74f6f5db43351bca036c25ab"));
    auto txUrl = WRAPS(TWCoinTypeConfigurationGetTransactionURL(TWCoinTypeWestend, txId.get()));
    auto accId = WRAPS(TWStringCreateWithUTF8Bytes("5Gb8qgpPJKd34to1oNiz2AqaLvhqSadpg24tHwCYFiu1Z27M"));
    auto accUrl = WRAPS(TWCoinTypeConfigurationGetAccountURL(TWCoinTypeWestend, accId.get()));
    auto id = WRAPS(TWCoinTypeConfigurationGetID(TWCoinTypeWestend));
    auto name = WRAPS(TWCoinTypeConfigurationGetName(TWCoinTypeWestend));

    ASSERT_EQ(TWCoinTypeConfigurationGetDecimals(TWCoinTypeWestend), 12);
    ASSERT_EQ(TWBlockchainPolkadot, TWCoinTypeBlockchain(TWCoinTypeWestend));
    ASSERT_EQ(0x0, TWCoinTypeP2shPrefix(TWCoinTypeWestend));
    ASSERT_EQ(0x0, TWCoinTypeStaticPrefix(TWCoinTypeWestend));
    assertStringsEqual(symbol, "WND");
    assertStringsEqual(txUrl, "https://westend.subscan.io/extrinsic/0xb53b5362b18c7458737b8133ac80fa36b1b159ac74f6f5db43351bca036c25ab");
    assertStringsEqual(accUrl, "https://westend.subscan.io/account/5Gb8qgpPJKd34to1oNiz2AqaLvhqSadpg24tHwCYFiu1Z27M");
    assertStringsEqual(id, "westend");
    assertStringsEqual(name, "Westend");
}
