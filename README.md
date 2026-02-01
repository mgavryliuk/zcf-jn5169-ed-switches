- [Overview](#overview)
- [Getting Started](#getting-started)
- [Devices](#devices)
- [Flashing](#flashing)
- [Pairing after flashing](pairing-after-flashing)
- [JN5169 Documentation](#jn5169-documentation)

# Overview
This repository provides custom firmware implementations for JN5169 MCU-based devices.

Pre-built firmwares can be found in the [zigbee-custom-firmwares](https://github.com/mgavryliuk/zigbee-custom-firmwares) repository.

# Getting Started
This project uses VS Code and [Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers) for development and building.
1. Install [Visual Studio Code](https://code.visualstudio.com/).
2. Follow the [Dev Containers tutorial](https://code.visualstudio.com/docs/devcontainers/tutorial) and open the project in the remote environment.
    - Use `.devcontainer/scripts/install-vscode-extensions.sh` to install extenstion into container if they were not installed automatically.
3. Download SDK `JN-SW-4170` from NXP site and add into sdk directory.
4. Click the `Build` button to compile the project.

> **Note!** Function `eZCL_ReportAttribute` in `sdk/Components/ZCIF/Source/zcl.c` was adjusted manually to disable default response.
> ```c
>        // Write command header
>        u16Offset = u16ZCL_WriteCommandHeader(
>              hAPduInst, eFrameType,
>              FALSE, 0,
>              TRUE,
>              TRUE, // changed by hands to disable default response. Original: FALSE
>              u8Seq, E_ZCL_REPORT_ATTRIBUTES);
> ```

# Devices
| Device | Description | Documentation | Build Preset |
|--------|-------------|---------------|--------------|
| WXKG06LM | Wireless remote switch D1 (single rocker) | [Documentation](firmwares/WXKG06LM/README.md) | `WXKG06LM` |
| WXKG07LM | Wireless remote switch D1 (double rocker) | [Documentation](firmwares/WXKG07LM/README.md) | `WXKG07LM` |
| WXKG11LM | Wireless mini switch | [Documentation](firmwares/WXKG11LM/README.md) | `WXKG11LM` |

# Flashing
> ⚠️ **Important**
> - FTDI **must be set to 3.3V**. Using 5V will permanently damage the device.
> - Do not power the device from any other source while FTDI 3.3V is connected.
> - `MISO → GND` is required **only during bootloader entry**.
> - Flashing works only on Windows and is not possible to a chip with `CRP_LEVEL2` protection set

1. Connect the FTDI adapter

| Target Pad | FTDI Pin | Notes |
|------------|----------|-------|
| **TDO**    | **RX**   | Data from device to FTDI |
| **TDI**    | **TX**   | Data from FTDI to device |
| **MISO**   | **GND**  | Connect to GND **only during bootloader mode** |
| **DC3V**   | **3.3V** | Power from FTDI (ensure FTDI is set to 3.3V) |
| **RESETN** | **GND (via button)** | Pulling RESETN low resets the device. Use a momentary button, not a permanent short. |
| **GND**    | **GND**  | Common ground |

2. Download and install [JN51xx Production Flash Programmer](https://www.nxp.com/downloads/en/software-development-kits/JN-SW-4107.zip)

3. Flash the firmware
```powershell
# Find your FTDI port
PS C:\NXP\ProductionFlashProgrammer> .\JN51xxProgrammer.exe -l
Available connections:
COM5

# Check device config
PS C:\NXP\ProductionFlashProgrammer> .\JN51xxProgrammer.exe -V 0 -s COM5 --deviceconfig
  COM5: Detected JN5169 with MAC address 00:15:8D:00:01:B9:6A:FE
  COM5: Device configuration: JTAG_DISABLE_CPU,VBO_200,CRP_LEVEL1,EXTERNAL_FLASH_NOT_ENCRYPTED,EXTERNAL_FLASH_LOAD_ENABLE

# Flash the firmware. Example (do not copy blindly):
PS C:\NXP\ProductionFlashProgrammer> .\JN51xxProgrammer.exe -V 0 -s COM5 -f D:\Programs\bstudio_nxp\workspace\Aqara_D1_ALT\build\src\AQARA_D1_ALT.bin
```
> If flashing fails, check:
> - `MISO → GND` was connected during bootloader entry
> - The FTDI adapter connected properly
> - The correct FTDI COM port is used (`JN51xxProgrammer.exe -l`)


# Pairing after flashing

1. **Remove the old device** from Zigbee2MQTT and restart Zigbee2MQTT.  

2. **Add the custom converter**  
   Copy the converter file from this repository into your Zigbee2MQTT `external_converters` directory and restart Zigbee2MQTT again.

3. **Permin join in Zigbee2MQTT**  

4. **Start pairing mode**  
   Press and hold **both buttons** (or the single button on 1-button models), until the LED starts **rapidly blinking**.

5. **Bind the Power Configuration cluster**  
    > Do this **even if a binding already exists** — otherwise battery reports will not work.
    Go to the device **Bind** tab and press **Bind** with the following settings:

   - Source endpoint: `1`  
   - Destination endpoint: `1`  
   - Cluster: `genPowerCfg`  


# JN5169 Documentation
[Product page](https://www.nxp.com/products/JN5169)</br>
[Support Resources for JN516x MCUs](https://www.nxp.com/products/wireless-connectivity/zigbee/support-resources-for-jn516x-mcus:SUPPORT-RESOURCES-JN516X-MCUS)</br>
[JN516x/7x Zigbee 3.0](https://www.nxp.com/pages/jn516x-7x-zigbee-3-0:ZIGBEE-3-0)</br>
[Data Sheet: JN516x](docs/JN516X.pdf)</br>
[Data Sheet: JN5169](docs/JN5169.pdf)</br>
[IEEE 802.15.4 Stack (JN-UG-3024)](docs/JN-UG-3024.pdf)</br>
[ZigBee 3.0 Stack (JN-UG-3113)](docs/JN-UG-3113.pdf)</br>
[ZigBee 3.0 Devices (JN-UG-3114)](docs/JN-UG-3114.pdf)</br>
[ZigBee Cluster Library (for ZigBee 3.0) (JN-UG-3115)](docs/JN-UG-3115.pdf)</br>
[JN51xx Core Utilities (JN-UG-3116)](docs/JN-UG-3116.pdf)</br>
[JN516x Integrated Peripherals API (JN-UG-3087)](docs/JN-UG-3087.pdf)</br>
[JN51xx Production Flash Programmer (JN-UG-3099)](docs/JN-UG-3099.pdf)</br>
[JN51xx Boot Loader Operation (JN-AN-1003)](docs/JN-AN-1003.pdf)
