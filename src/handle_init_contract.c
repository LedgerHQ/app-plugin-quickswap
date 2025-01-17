#include "quickswap_plugin.h"

// Called once to init.
void handle_init_contract(ethPluginInitContract_t *msg) {
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        PRINTF("Wrong interface version: expected %d got %d\n",
               ETH_PLUGIN_INTERFACE_VERSION_LATEST,
               msg->interfaceVersion);
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    if (msg->pluginContextLength < sizeof(quickswap_parameters_t)) {
        PRINTF("QuickSwap context size too big: expected %d got %d\n",
               sizeof(quickswap_parameters_t),
               msg->pluginContextLength);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    quickswap_parameters_t *context = (quickswap_parameters_t *) msg->pluginContext;
    memset(context, 0, sizeof(*context));
    context->valid = 1;

    for (uint8_t i = 0; i < NUM_QUICKSWAP_SELECTORS; i++) {
        if (memcmp((uint8_t *) PIC(QUICKSWAP_SELECTORS[i]), msg->selector, SELECTOR_SIZE) == 0) {
            context->selectorIndex = i;
            break;
        }
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case SWAP_EXACT_TOKENS_FOR_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH:
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            context->next_param = AMOUNT_SENT;
            break;
        case SWAP_TOKENS_FOR_EXACT_TOKENS:
        case SWAP_EXACT_ETH_FOR_TOKENS:
        case SWAP_ETH_FOR_EXACT_TOKENS:
        case SWAP_TOKENS_FOR_EXACT_ETH:
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            context->next_param = AMOUNT_RECEIVED;
            break;

        case ADD_LIQUIDITY:
        case ADD_LIQUIDITY_ETH:
        case REMOVE_LIQUIDITY:
        case REMOVE_LIQUIDITY_ETH:
        case REMOVE_LIQUIDITY_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            context->next_param = TOKEN_SENT;
            break;

        default:
            PRINTF("Missing selectorIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
