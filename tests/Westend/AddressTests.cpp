// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "HexCoding.h"
#include "Westend/Address.h"
#include "PublicKey.h"
#include "PrivateKey.h"
#include <gtest/gtest.h>
#include <vector>

using namespace TW;
using namespace TW::Westend;

TEST(WestendAddress, Validation) {
    // Substrate ed25519
    ASSERT_TRUE(Address::isValid("5FqqU2rytGPhcwQosKRtW1E3ha6BJKAjHgtcodh71dSyXhoZ"));
    // Polkadot ed25519
    ASSERT_FALSE(Address::isValid("15AeCjMpcSt3Fwa47jJBd7JzQ395Kr2cuyF5Zp4UBf1g9ony"));
    // Polkadot sr25519
    ASSERT_FALSE(Address::isValid("15AeCjMpcSt3Fwa47jJBd7JzQ395Kr2cuyF5Zp4UBf1g9ony"));
    // Bitcoin
    ASSERT_FALSE(Address::isValid("1ES14c7qLb5CYhLMUekctxLgc1FV2Ti9DA"));
    // Kusama ed25519
    ASSERT_FALSE(Address::isValid("FHKAe66mnbk8ke8zVWE9hFVFrJN1mprFPVmD5rrevotkcDZ"));
    // Kusama secp256k1
    ASSERT_FALSE(Address::isValid("FxQFyTorsjVsjjMyjdgq8w5vGx8LiA1qhWbRYcFijxKKchx"));
    // Kusama sr25519
    ASSERT_FALSE(Address::isValid("EJ5UJ12GShfh7EWrcNZFLiYU79oogdtXFUuDDZzk7Wb2vCe"));
    // Westend ed25519
    ASSERT_TRUE(Address::isValid("5GgzZ4BLuvYNtm2cxKqcckS2HwtvH2vu7LZEpR2iHWAQZTMf"));
    // Westend secp256k1
    ASSERT_TRUE(Address::isValid("5EPKW4cefqMDD5apPTUKPbovUKN89rtJasgX3AcHg89vvwtx"));
    // Westend sr25519
    ASSERT_TRUE(Address::isValid("5HeXhvKuXLc5cgQgaseCDJfPDWwHszTKTJ8dY8hHJdM5BAko"));
}

TEST(WestendAddress, FromPrivateKey) {
    // from subkey: tiny escape drive pupil flavor endless love walk gadget match filter luxury
    auto privateKey = PrivateKey(parse_hex("0xa21981f3bb990c40837df44df639541ff57c5e600f9eb4ac00ed8d1f718364e5"));
    auto address = Address(privateKey.getPublicKey(TWPublicKeyTypeED25519));
    ASSERT_EQ(address.string(), "5C8ssaTbSTxDtTRf97rJ8cDrLzeQDULHHEnq4ngjjRMMoQRw");
}

TEST(WestendAddress, FromPublicKey) {
    auto publicKey = PublicKey(parse_hex("0x032eb287017c5cde2940b5dd062d413f9d09f8aa44723fc80bf46b96c81ac23d"), TWPublicKeyTypeED25519);
    auto address = Address(publicKey);
    ASSERT_EQ(address.string(), "5C8ssaTbSTxDtTRf97rJ8cDrLzeQDULHHEnq4ngjjRMMoQRw");
}

TEST(WestendAddress, FromString) {
    auto address = Address("5C8ssaTbSTxDtTRf97rJ8cDrLzeQDULHHEnq4ngjjRMMoQRw");
    ASSERT_EQ(address.string(), "5C8ssaTbSTxDtTRf97rJ8cDrLzeQDULHHEnq4ngjjRMMoQRw");
}
