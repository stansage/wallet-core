// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Polkadot/Signer.h"
#include "Polkadot/Extrinsic.h"
#include "SS58Address.h"
#include "HexCoding.h"
#include "PrivateKey.h"
#include "PublicKey.h"
#include "proto/Polkadot.pb.h"
#include "uint256.h"

#include <TrustWalletCore/TWSS58AddressType.h>
#include <gtest/gtest.h>


namespace TW::Polkadot {
    extern PrivateKey privateKey;
    extern PublicKey toPublicKey;
    auto genesisHashWND = parse_hex("e143f23803ac50e8f6f8e62695d1ce9e4e1d68aa36c1cd2cfd15340213f3423e");

TEST(PolkadotSigner, SignTransferWND) {
    auto blockHash = parse_hex("4955dd4813f3e91ef3fd5a825b928af2fc50a71380085f753ccef00bb1582891");
    auto toAddress = SS58Address(toPublicKey, TWSS58AddressTypeWestend);

    auto input = Proto::SigningInput();
    input.set_block_hash(blockHash.data(), blockHash.size());
    input.set_genesis_hash(genesisHashWND.data(), genesisHashWND.size());
    input.set_nonce(0);
    input.set_spec_version(2019);
    input.set_private_key(privateKey.bytes.data(), privateKey.bytes.size());
    input.set_network(Proto::Network::WESTEND);
    input.set_transaction_version(2);

    auto balanceCall = input.mutable_balance_call();
    auto &transfer = *balanceCall->mutable_transfer();
    auto value = store(uint256_t(12345));
    transfer.set_to_address(toAddress.string());
    transfer.set_value(value.data(), value.size());

    auto extrinsic = Extrinsic(input);
    auto preimage = extrinsic.encodePayload();
    auto output = Signer::sign(input);

    ASSERT_EQ(hex(preimage), "04008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48e5c0000000e307000002000000e143f23803ac50e8f6f8e62695d1ce9e4e1d68aa36c1cd2cfd15340213f3423e4955dd4813f3e91ef3fd5a825b928af2fc50a71380085f753ccef00bb1582891");
    ASSERT_EQ(hex(output.encoded()), "25028488dc3417d5058ec4b4503e0c12ea1a0a89be200fe98922423d4334014fa6b0ee00eda3f60383419f4ab891bbc6d346f3246d1ab83f32d57b562b2e1eeb5bd9807b803be28a2d78708adb6a2d70c23ff5dabca69b92015edb202af81e39b2e53d0e00000004008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48e5c0");
}

} // namespace
