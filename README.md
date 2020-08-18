[![MCHP](images/microchip.png)](https://www.microchip.com)

# AVR128DB48 Curiosity Nano OPAMP Demonstration Firmware

The AVR128DB48 Curiosity Nano Evaluation Kit is preprogramed to provide a number of different OPAMP configurations, depending on the state of the three input pins PC4, PC5 and PC6. Each of these pins is internally pulled high, If left unconnected the corresponding pin is high and reads logic '1'. Connect the pin directly to ground for logic '0'.

In addition to the OPAMP configuration the onboard LED0 will blink a number of times equal to the current setting. To check current setting and/or reconfigure, click the on board switch(SW0).

![Modes of Operation](images/modes_of_operation.png)

## Related Documentation

* [AVR128DB48 Curiosity Nano User Guide](https://microchip.com/DSxxxxxxxxxx) <!-- TODO: Update link once assigned -->
* [AVR128DB48 Device Page](https://www.microchip.com/wwwproducts/en/AVR128DB48)

## Software Used

* [Atmel Studio](https://www.microchip.com/mplab/avr-support/atmel-studio-7) 7.0.2397 or later
* Atmel Studio AVR-Dx_DFP version 1.2.56 or later

## Hardware Used

* [AVR128DB48 Curiosity Nano](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EV35L43A)

## Operation

#### Modes of Operation

The board is in standby sleep mode with the OPAMPs enabled in between reconfiguration of the OPAMPs.

| PC4 | PC5 | PC6 | Configuration                  |  
| --- | --- | --- | -------------                  |
|  0  |  1  |  1  | 1 - Connected directly to pins |
|  1  |  0  |  1  | 2 - Voltage follower           |
|  0  |  0  |  1  | 3 - Non-Inverting PGA          |
|  1  |  1  |  0  | 4 - Inverting PGA              |
|  0  |  1  |  0  | 5 - Differential amplifier     |
|  1  |  0  |  0  | 6 - Instrumentation amplifier  |  

If the pins PC4, PC5 and PC6 has a different configuration than in the table above, the AVR defaults to Configuration 1, Connected directly to pins.

#### OPAMP Pins on AVR128DB48

| OPAMPn | Positive input (INP) | Negative input (INN) | Output (OUT) |
| ------ | -------------------- | -------------------- | ------------ |
| OPAMP0 |         PD1          |          PD3         |     PD2      |
| OPAMP1 |         PD4          |          PD7         |     PD5      |
| OPAMP2 |         PE1          |          PE3         |     PE2      |

### Configuration 1: Connected Directly to Pins

In the *Connected directly to pins* configuration each of the internal op amp inputs and outputs are connected directly to the corresponding I/O pins. This means that each op amp can be used as a standalone op amp with use of external discrete components to achieve a specific functionality.

![Connected directly to pins](images/OPn_PinConnected.png)

### Configuration 2: Voltage Follower

In the *Voltage follower* mode each op amp is configured as voltage followers, this means that INP and the OUT are connected to the I/O pins while INN is internally connected to the op amp output. 

![Voltage follower](images/OPn_VoltageFollower.png)

### Configuration 3: Non-Inverting PGA (Programable Gain Amplifier)

In the *Non-inverting PGA* mode each op amp is configured as non-inverting PGA using the internal resistor lader. INP and the OUT are connected to the I/O pins. Each the op amp is configured with different gain as listed below: 

| OPAMPn | Gain | Positive input (INP) | Output (OUT) |
| :----: | :--: | :------------------: | :----------: |
| OPAMP0 |  4x  |         PD1          |     PD2      |
| OPAMP1 |  8x  |         PD4          |     PD5      |
| OPAMP2 | 16x  |         PE1          |     PE2      |

![Non-Inverting PGA](images/OPn_NonInvertingPGA.png)

### Configuration 4: Inverting PGA

In the *Inverting PGA* configuration each of the OPAMPs are configured as inverting PGAs using the internal resistor lader.

Each op amp is configured with different gain as listed below:

| OPAMPn | Gain |   RESMUXBOT (Vin)   | Output (OUT) |
| :----: | :--: | :-----------------: | :----------: |
| OPAMP0 |  3x  |        PD1          |     PD2      |
| OPAMP1 |  7x  |        PD4          |     PD5      |
| OPAMP2 | 15x  |        PE1          |     PE2      |

![Inverting PGA](images/OPn_InvertingPGA.png)

### Configuration 5: Differential Amplifier

In the *Differential amplifier* configuration OPAMP0 and OPAMP1 is set up as a differential amplifier with a gain of 15x and the following inpup/outut pins:

| V1 input | V2 input | Output |
| -------- | -------- | ------ |
|   PD1    |   PD4    |   PD5  |

![Differential amplifier](images/OPn_TwoOaDiffAmp.png)

OPAMP2 is configured to be connected directly to its pins, listed above in section "OPAMP Pin connections"

### Configuration 6: Instrumentation Amplifier

In the *Instrumentation amplifier* configuration all three OPAMPs are needed. The OPAMPs are connected as shown in the figure below.

| V1 input | V2 input | Output |
| -------- | -------- | ------ |
|   PD4    |   PD1    |   PE2  |

The gain is set through a combination of OP1 and OP2 resistor ladder network. The gain of the *Instrumentation amplifier* configuration has been selected to be x15.

![Instrumentation amplifier](images/OPn_InstruAmplifier.png)
