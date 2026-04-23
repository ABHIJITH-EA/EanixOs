# PIT (Programmable Interval Timer)

## Overview

The **PIT (8253/8254)** is used to generate periodic interrupts for timing.

It is commonly used to create a **system timer (ticks)** that the kernel can use for delays, scheduling, and timekeeping.

---

## Why We Needed This

* CPU has no built-in concept of time
* Needed a reliable periodic interrupt
* Required for:

  * Kernel timing
  * Future task scheduling
  * Delays / sleep functions

---

## What We Implemented

### 1. PIT Initialization

* Configured PIT to operate in **square wave mode (mode 3)**
* Set a frequency divisor to control interrupt rate

---

### 2. Timer Frequency Setup

* Base PIT frequency: **1193182 Hz**
* Divided it to generate periodic interrupts (e.g., 100 Hz)

---

### 3. IRQ0 Timer Interrupt

* PIT is connected to **IRQ0**
* On each tick:

  * Interrupt is triggered
  * Kernel timer handler is executed

---

### 4. Tick Counter

* Added a global tick counter
* Increments on every timer interrupt

---

## Result

* System now has a **working periodic timer**
* Kernel can track time using ticks
* Foundation for:

  * Sleep/delay functions
  * Preemptive multitasking (future)


## Notes

* PIT command port: `0x43`
* PIT channel 0 data port: `0x40`
* Connected to IRQ0 (first hardware interrupt)
