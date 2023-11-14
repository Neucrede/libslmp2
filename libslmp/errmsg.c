/*
 * Copyright (C) Neucrede <neucrede@sina.com>
 * Version: 1.0
 * License: BSD 2-Clause License
 */

#include "slmp/slmpdef.h"
#include "slmp/slmperr.h"

#include "slmp_intl.h"

const err_msg_desc_t err_msg[] = {
    { SLMP_ERROR_SUCCESS, "Operation successfully completed." },

    { SLMP_ERROR_OUT_OF_MEMORY, "Out of memory." },
    { SLMP_ERROR_INVALID_ARGUMENTS, "Invalid arguments." },
    { SLMP_ERROR_BUFFER_TOO_SHORT, "Buffer too short." },
    { SLMP_ERROR_MODULE_INIT_FAILED, "Module initialization failed." },
    { SLMP_ERROR_NOT_INITIALIZED, "Not initialized." },
    { SLMP_ERROR_PKTIO_CONTEXT_CORRUPTED, "Packet IO context is corrupted." },
    { SLMP_ERROR_OPERATION_FAILED, "Operation was failed." },
    { SLMP_ERROR_TIMEOUT, "Timeout." },
    { SLMP_ERROR_BAD_FTYPE, "Invalid FTYPE value." },
    { SLMP_ERROR_BAD_STREAM_TYPE, "Invalid stream type value." },
    { SLMP_ERROR_BAD_FRAME_PACKET, "Invalid frame packet." },
    { SLMP_ERROR_RESOURCE_IS_BUSY, "Resource is busy." },
    { SLMP_ERROR_DATA_NOT_YET_AVAILABLE, "Data is not yet available now." },
    { SLMP_ERROR_OPERATION_NOT_SUPPORTED, "Requested operation is not supported." },
    { SLMP_ERROR_BAD_ADDRESS_WIDTH, "Bad address width." },
    { SLMP_ERROR_INCORRECT_SIZE, "Incorrect size." },
    { SLMP_ERROR_INVALID_POINTER, "Invalid pointer value." },
    { SLMP_ERROR_INCONSISTENT_FRAME_TYPES, "Inconsistent frame types." },
    { SLMP_ERROR_RUN_OUT_OF_INTERNAL_BUFFER, "Run out of internal buffer." },
    { SLMP_ERROR_DATA_TOO_LARGE, "Data too large." },

    { SLMP_ERROR_SOCKET_CREATION_FAILED, "Failed to create socket." },
    { SLMP_ERROR_SET_OPTIONS_FAILED, "Failed to set socket options." },
    { SLMP_ERROR_BIND_FAILED, "Failed to bind the socket to the specified address." },
    { SLMP_ERROR_LISTEN_FAILED, "Failed to listen on specified address." },
    { SLMP_ERROR_ADDRESS_NOT_AVAILABLE, "Address not available." },
    { SLMP_ERROR_NO_CONNECTION, "No connection." },
    { SLMP_ERROR_CONNECT_FAILED, "Failed to connect." },
    { SLMP_ERROR_SOCKET_ERROR, "General socket error." },
    { SLMP_ERROR_STILL_CONNECTED, "Still connected." },
    { SLMP_ERROR_NOT_OPENED, "Connection not opened." },
    { SLMP_ERROR_ACCEPT_FAILED, "Failed to accept a connection." },
    { SLMP_ERROR_ALREADY_OPEN, "Connection is already opened." },
    { SLMP_ERROR_CONNECTION_CLOSED, "Connection closed." },
    

    /* The following line marks the end of array. DO NOT DELETE. */
    { 0xABCD0123, NULL }
};

const err_msg_desc_t endcode_msg[] = {
    { SLMP_ENDCODE_SUCCESS, "Success." },
    { SLMP_ENDCODE_BAD_COMMAND, "Invalid command and sub-command combination." },
    { SLMP_ENDCODE_BAD_REQUEST_CONTENT, "Invalid request message content." },
    { SLMP_ENDCODE_REQUEST_DATA_LENGTH_MISMATCH, "Request data length not match." },
    { SLMP_ENDCODE_RESOURCE_BUSY, "The request cannot be processed because another request is still being processed." },
    { SLMP_ENDCODE_REQUEST_MESSAGE_TOO_LARGE, "The length of request message exceeds the limit." },
    { SLMP_ENDCODE_RESPONSE_MESSAGE_TOO_LARGE, "The length of response message exceeds the limit." },
    { SLMP_ENDCODE_SERVER_INFO_NOT_EXIST, "The specified server information number does not exist." },
    { SLMP_ENDCODE_PARAM_ID_NOT_EXIST, "The specified parameter ID does not exist." },
    { SLMP_ENDCODE_WRITE_MUTEX_START_NOT_PERFORMED, "The request cannot be processed because the writing mutual exclusion start process has not been performed." },
    { SLMP_ENDCODE_DIVIDED_MESSAGE_RECEIVE_TIMEOUT, "The divided messages for a frame could not be received within the time limit." },
    { SLMP_ENDCODE_DUPLICATED_DIVIDED_MESSAGE, "Duplicated divided message was received." },
    { SLMP_ENDCODE_DIVIDED_MESSAGE_DATA_ERROR, "Divided message data error." },
    { SLMP_ENDCODE_DIVIDED_MESSAGE_LOST, "The message was lost due to an error occurred in the receive side." },
    { SLMP_ENDCODE_DIVISON_NOT_SUPPORTED_BY_TARGET, "The request target does not support message division." },

    /* The following line marks the end of array. DO NOT DELETE. */
    { 0xABCD0123, NULL }
};

