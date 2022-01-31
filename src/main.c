/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "os.h"
#include "cx.h"

#include "glyphs.h"

#include "quickswap_plugin.h"

// Function: swapExactTokensForTokens(uint256 amountIn, uint256 amountOutMin, address[] path,
// address to, uint256 deadline)
// MethodID: 0x38ed1739
static const uint8_t SWAP_EXACT_TOKENS_FOR_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x38,
                                                                             0xed,
                                                                             0x17,
                                                                             0x39};

// Function: swapExactTokensForETH(uint256 amountIn, uint256 amountOutMin, address[] path, address
// to, uint256 deadline)
// MethodID: 0x18cbafe5
static const uint8_t SWAP_EXACT_TOKENS_FOR_ETH_SELECTOR[SELECTOR_SIZE] = {0x18, 0xcb, 0xaf, 0xe5};

// Function: swapExactETHForTokens(uint256 amountOutMin, address[] path, address to, uint256
// deadline)
// MethodID : 0x7ff36ab5
static const uint8_t SWAP_EXACT_ETH_FOR_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x7f, 0xf3, 0x6a, 0xb5};

// Function: swapTokensForExactTokens(uint256 amountOut, uint256 amountInMax, address[] path,
// address to, uint256 deadline)
// MethodID : 0x8803dbee
static const uint8_t SWAP_TOKENS_FOR_EXACT_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x88,
                                                                             0x03,
                                                                             0xdb,
                                                                             0xee};

// Function: swapExactTokensForTokensSupportingFeeOnTransferTokens(uint256 amountIn, uint256
// amountOutMin, address[] path, address to, uint256 deadline)
// MethodID: 0x5c11d795
static const uint8_t
    SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x5c,
                                                                                              0x11,
                                                                                              0xd7,
                                                                                              0x95};

// Function: swapETHForExactTokens(uint256 amountOut, address[] path, address to, uint256 deadline)
// MethodID: 0xfb3bdb41
static const uint8_t SWAP_ETH_FOR_EXACT_TOKENS_SELECTOR[SELECTOR_SIZE] = {0xfb, 0x3b, 0xdb, 0x41};

// Function: swapExactTokensForETHSupportingFeeOnTransferTokens(uint256 amountIn, uint256
// amountOutMin, address[] path, address to, uint256 deadline)
// MethodID: 0x791ac947
static const uint8_t
    SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x79,
                                                                                           0x1a,
                                                                                           0xc9,
                                                                                           0x47};

// Function: swapTokensForExactETH(uint256 amountOut, uint256 amountInMax, address[] path, address
// to, uint256 deadline)
// MethodID: 0x4a25d94a
static const uint8_t SWAP_TOKENS_FOR_EXACT_ETH_SELECTOR[SELECTOR_SIZE] = {0x4a, 0x25, 0xd9, 0x4a};

// Function: swapExactETHForTokensSupportingFeeOnTransferTokens(uint256 amountOutMin, address[]
// path, address to, uint256 deadline)
// MethodID: 0xb6f9de95
static const uint8_t
    SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR[SELECTOR_SIZE] = {0xb6,
                                                                                           0xf9,
                                                                                           0xde,
                                                                                           0x95};

// Function: addLiquidity(address tokenA, address tokenB, uint256 amountADesired, uint256
// amountBDesired, uint256 amountAMin, uint256 amountBMin, address to, uint256 deadline)
// MethodID: 0xe8e33700
static const uint8_t ADD_LIQUIDITY_SELECTOR[SELECTOR_SIZE] = {0xe8, 0xe3, 0x37, 0x00};

// Function: addLiquidityETH(address token, uint256 amountTokenDesired, uint256 amountTokenMin,
// uint256 amountETHMin, address to, uint256 deadline)
// MethodID: 0xf305d719
static const uint8_t ADD_LIQUIDITY_ETH_SELECTOR[SELECTOR_SIZE] = {0xf3, 0x05, 0xd7, 0x19};

// Function: removeLiquidity(address tokenA, address tokenB, uint256 liquidity, uint256 amountAMin,
// uint256 amountBMin, address to, uint256 deadline)
// MethodID: 0xbaa2abde
static const uint8_t REMOVE_LIQUIDITY_SELECTOR[SELECTOR_SIZE] = {0xba, 0xa2, 0xab, 0xde};

// Function: removeLiquidityETH(address token, uint256 liquidity, uint256 amountTokenMin, uint256
// amountETHMin, address to, uint256 deadline)
// MethodID: 0x02751cec
static const uint8_t REMOVE_LIQUIDITY_ETH_SELECTOR[SELECTOR_SIZE] = {0x02, 0x75, 0x1c, 0xec};

// Function: removeLiquidityWithPermit(address tokenA, address tokenB, uint256 liquidity, uint256
// amountAMin, uint256 amountBMin, address to, uint256 deadline, bool approveMax, uint8 v, bytes32
// r, bytes32 s)
// MethodID: 0x2195995c
static const uint8_t REMOVE_LIQUIDITY_WITH_PERMIT_SELECTOR[SELECTOR_SIZE] = {0x21,
                                                                             0x95,
                                                                             0x99,
                                                                             0x5c};

// Function: removeLiquidityETHWithPermit(address token, uint256 liquidity, uint256 amountTokenMin,
// uint256 amountETHMin, address to, uint256 deadline, bool approveMax, uint8 v, bytes32 r, bytes32
// s)
// MethodID: 0xded9382a
static const uint8_t REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SELECTOR[SELECTOR_SIZE] = {0xde,
                                                                                 0xd9,
                                                                                 0x38,
                                                                                 0x2a};

// Array of all the different quickswap selectors.
const uint8_t *const QUICKSWAP_SELECTORS[NUM_QUICKSWAP_SELECTORS] = {
    SWAP_EXACT_TOKENS_FOR_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_ETH_SELECTOR,
    SWAP_EXACT_ETH_FOR_TOKENS_SELECTOR,
    SWAP_TOKENS_FOR_EXACT_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    SWAP_ETH_FOR_EXACT_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    SWAP_TOKENS_FOR_EXACT_ETH_SELECTOR,
    SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    ADD_LIQUIDITY_SELECTOR,
    ADD_LIQUIDITY_ETH_SELECTOR,
    REMOVE_LIQUIDITY_SELECTOR,
    REMOVE_LIQUIDITY_ETH_SELECTOR,
    REMOVE_LIQUIDITY_WITH_PERMIT_SELECTOR,
    REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SELECTOR};

// QuickSwap uses `0xeeeee` as a dummy address to represent ETH.
const uint8_t QUICKSWAP_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                       0x00, 0x00, 0x00, 0x00, 0x10, 0x10};

// Used to indicate that the beneficiary should be the sender.
const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void quickswap_plugin_call(int message, void *parameters) {
    switch (message) {
        case ETH_PLUGIN_INIT_CONTRACT:
            handle_init_contract(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_PARAMETER:
            handle_provide_parameter(parameters);
            break;
        case ETH_PLUGIN_FINALIZE:
            handle_finalize(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_TOKEN:
            handle_provide_token(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_ID:
            handle_query_contract_id(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            handle_query_contract_ui(parameters);
            break;
        default:
            PRINTF("Unhandled message %d\n", message);
            break;
    }
}

void call_app_ethereum() {
    unsigned int libcall_params[3];
    libcall_params[0] = (unsigned int) "Ethereum";
    libcall_params[1] = 0x100;
    libcall_params[2] = RUN_APPLICATION;
    os_lib_call((unsigned int *) &libcall_params);
}

__attribute__((section(".boot"))) int main(int arg0) {
    // exit critical section
    __asm volatile("cpsie i");

    // ensure exception will work as planned
    os_boot();

    // Try catch block. Please read the docs for more information on how to use those!
    BEGIN_TRY {
        TRY {
            // Low-level black magic.
            check_api_level(CX_COMPAT_APILEVEL);
            // Check if we are called from the dashboard.
            if (!arg0) {
                // called from dashboard, launch Ethereum app
                call_app_ethereum();
                return 0;
            } else {
                // Not called from dashboard: called from the ethereum app!
                const unsigned int *args = (unsigned int *) arg0;

                // If `ETH_PLUGIN_CHECK_PRESENCE` is set, this means the caller is just trying to
                // know whether this app exists or not. We can skip `quickswap_plugin_call`.
                if (args[0] != ETH_PLUGIN_CHECK_PRESENCE) {
                    quickswap_plugin_call(args[0], (void *) args[1]);
                }
                os_lib_end();
            }
        }
        FINALLY {
        }
    }
    END_TRY;

    return 0;
}
