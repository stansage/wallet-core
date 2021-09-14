// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

import WalletCore
import XCTest

class WestendTests: XCTestCase {

    func testAddressValidation() {
        let westend = CoinType.westend
        // polkadot sr25519
        XCTAssertFalse(westend.validate(address: "14PhJGbzPxhQbiq7k9uFjDQx3MNiYxnjFRSiVBvBBBfnkAoM"))
        // cosmos
        XCTAssertFalse(westend.validate(address: "cosmos1l4f4max9w06gqrvsxf74hhyzuqhu2l3zyf0480"))
        // Bitcoin p2sh
        XCTAssertFalse(westend.validate(address: "3317oFJC9FvxU2fwrKVsvgnMGCDzTZ5nyf"))
        // Kusama
        XCTAssertFalse(polkadot.validate(address: "ELmaX1aPkyEF7TSmYbbyCjmSgrBpGHv9EtpwR2tk1kmpwvG"))
        // Westend 
        XCTAssertTrue(polkadot.validate(address: "5GgzZ4BLuvYNtm2cxKqcckS2HwtvH2vu7LZEpR2iHWAQZTMf"))
    }

    func testAddress() {
        let key = PrivateKey(data: Data(hexString: "0x85fca134b3fe3fd523d8b528608d803890e26c93c86dc3d97b8d59c7b3540c97")!)!
        let pubkey = key.getPublicKeyEd25519()
        let address = AnyAddress(publicKey: pubkey, coin: .westend)
        let addressFromString = AnyAddress(string: "5H9L3u7YHn1QGwgSzHuWJAoSpFyFABHQH2FH2rtqTbukURtY", coin: .kusama)!

        XCTAssertEqual(pubkey.data.hexString, "e0b3fcccfe0283cc0f8c105c68b5690aab8c5c1692a868e55eaca836c8779085")
        XCTAssertEqual(address.description, addressFromString.description)
        XCTAssertEqual(address.data.hexString, pubkey.data.hexString)
    }

    func testSigningTransfer() {
        // https://westend.subscan.io/extrinsic/0x9211b8f6500c78f4771d18289c6187ec59c2b1fb28e8324ee32a1f9a3303be7e
        // real key in 1p test
        let wallet = HDWallet.test
        let key = wallet.getKey(coin: .westend, derivationPath: "m/44'/354434'/0'")

        let genesisHash = Data(hexString: "0xe143f23803ac50e8f6f8e62695d1ce9e4e1d68aa36c1cd2cfd15340213f3423e")!
        let input = PolkadotSigningInput.with {
            $0.genesisHash = genesisHash
            $0.blockHash = genesisHash
            $0.nonce = 1
            $0.specVersion = 2019
            $0.balanceCall = PolkadotBalance.with {
                $0.transfer = PolkadotBalance.Transfer.with {
                    $0.toAddress = "5CPKyMWpbqEwHc1URZzfL7LwGbnF4muAg8VNkV1mwqC6vSTz"
                    // 10000000000 ~ 0.01 WND
                    $0.value = Data(hexString: "0x02540be400")!
                }
            }
            $0.network = .westend
            $0.transactionVersion = 2
            $0.privateKey = key.data
        }
        let output: PolkadotSigningOutput = AnySigner.sign(input: input, coin: .westend)

        XCTAssertEqual(output.encoded.hexString, "350284f41296779fd61a5bed6c2f506cc6c9ea93d6aeb357b9c69717193f434ba24ae7004221b8a8236eea1ae74d58c42d70e769c6b2a7cb9fe784bfb3beecfec128697b59cbb1f2126325974bfd31bddc759be0ec97782e403b9f59992152ec941abe0600040004000e33fdfb980e4499e5c3576e742a563b6a4fc0f6f598b1917fd7a6fe393ffc720700e40b5402")
    }
}