/*
 * Copyright (c) 2015-2020, Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __USB_VIDEO_CAMERA_H__
#define __USB_VIDEO_CAMERA_H__

#include "FreeRTOS.h"
#include "semphr.h"

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
#include "usb_device_video.h"

#include "usb_device_ch9.h"
#include "usb_device_descriptor.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)
#define CONTROLLER_ID kUSB_ControllerEhci0
#endif
#if defined(USB_DEVICE_CONFIG_KHCI) && (USB_DEVICE_CONFIG_KHCI > 0U)
#define CONTROLLER_ID kUSB_ControllerKhci0
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511FS) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)
#define CONTROLLER_ID kUSB_ControllerLpcIp3511Fs0
#endif
#if defined(USB_DEVICE_CONFIG_LPCIP3511HS) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)
#define CONTROLLER_ID kUSB_ControllerLpcIp3511Hs0
#endif

#if defined(__GIC_PRIO_BITS)
#define USB_DEVICE_INTERRUPT_PRIORITY (25U)
#endif

typedef struct _usb_video_camera_struct
{
    usb_device_handle deviceHandle;
    class_handle_t videoHandle;
    uint32_t currentMaxPacketSize;
    uint8_t *imageBuffer;
    uint8_t *lastImageBuffer;
    uint32_t imageBufferLength;
    usb_device_video_probe_and_commit_controls_struct_t *probeStruct;
    usb_device_video_probe_and_commit_controls_struct_t *commitStruct;
    usb_device_video_still_probe_and_commit_controls_struct_t *stillProbeStruct;
    usb_device_video_still_probe_and_commit_controls_struct_t *stillCommitStruct;
    uint32_t imageIndex;
    uint32_t currentTime;
    uint32_t *classRequestBuffer;
    uint32_t imagePosition;
    uint8_t *image_header;
    uint8_t currentFrameId;
    uint8_t waitForNewInterval;
    uint8_t currentStreamInterfaceAlternateSetting;
    uint8_t probeLength;
    uint8_t commitLength;
    uint8_t probeInfo;
    uint8_t commitInfo;
    uint8_t stillProbeLength;
    uint8_t stillCommitLength;
    uint8_t stillProbeInfo;
    uint8_t stillCommitInfo;
    uint8_t stillImageTransmission;
    volatile uint8_t stillImageTriggerControl;
    uint8_t fullBufferIndex;
    uint8_t currentConfiguration;
    uint8_t currentInterfaceAlternateSetting[USB_VIDEO_VIRTUAL_CAMERA_INTERFACE_COUNT];
    uint8_t speed;
    uint8_t attach;
} usb_video_camera_struct_t;

extern SemaphoreHandle_t g_DisplayFull, g_DisplayEmpty;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief UVC class set default.
 *
 * This function handles the CDC class specific requests.
 *
 * @return None
 */

void USB_DeviceVideoApplicationSetDefault(void);

/*!
 * @brief UVC class prepare video data.
 *
 * Prepare the image buffer and attach it to global struct.
 *
 * @return None
 */

void USB_DeviceVideoPrepareVideoData(void);

/*!
 * @brief UVC specific callback function.
 *
 * This function handles the UCV class specific requests.
 *
 * @param handle          The UVB handle.
 * @param event           The UVCclass event type.
 * @param param           The parameter of the class specific request.
 *
 * @return A USB error code or kStatus_USB_Success.
 */

usb_status_t USB_DeviceVideoCallback(class_handle_t handle, uint32_t event, void *param);

#endif /* __USB_VIDEO_CAMERA_H__ */
