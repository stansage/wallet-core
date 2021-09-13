// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

package com.trustwallet.core.app.blockchains.westend

import com.google.protobuf.ByteString
import com.trustwallet.core.app.utils.Numeric
import com.trustwallet.core.app.utils.toHexByteArray
import com.trustwallet.core.app.utils.toHexBytes
import com.trustwallet.core.app.utils.toHexBytesInByteString
import org.junit.Assert.assertEquals
import org.junit.Test
import wallet.core.jni.WestendSigner
import wallet.core.jni.proto.Westend

class TestWestendSigner {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    @Test
    fun WestendTransactionSigning() {
        val key = "0x8cdc538e96f460da9d639afc5c226f477ce98684d77fb31e88db74c1f1dd86b2".toHexBytesInByteString()
        val hash = "0xb0a8d493285c2df73290dfb7e61f870f17b41801197a149ca93654499ea3dafe".toHexBytesInByteString()

        val call = Polkadot.Balance.Transfer.newBuilder().apply {
            toAddress = "5CPKyMWpbqEwHc1URZzfL7LwGbnF4muAg8VNkV1mwqC6vSTz"
            value = "0x02540be400".toHexBytesInByteString()
        }

        val input = Polkadot.SigningInput.newBuilder().apply {
            genesisHash = hash
            blockHash = hash
            nonce = 1
            specVersion = 2019
            network = Polkadot.Network.Westend
            transactionVersion = 2
            privateKey = key
            balanceCall = Polkadot.Balance.newBuilder().apply {
                transfer = call.build()
            }.build()
        }

        val output = AnySigner.sign(input.build(), WESTEND, SigningOutput.parser())
        val encoded = Numeric.toHexString(output.encoded.toByteArray())

        val expected = "0x350284f41296779fd61a5bed6c2f506cc6c9ea93d6aeb357b9c69717193f434ba24ae7004221b8a8236eea1ae74d58c42d70e769c6b2a7cb9fe784bfb3beecfec128697b59cbb1f2126325974bfd31bddc759be0ec97782e403b9f59992152ec941abe0600040004000e33fdfb980e4499e5c3576e742a563b6a4fc0f6f598b1917fd7a6fe393ffc720700e40b5402"
        assertEquals(encoded, expected)
    }
}
