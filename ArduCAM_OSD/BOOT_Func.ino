/* ******************************************************************/
/* *********************** BOOT UP FUNCTIONS ********************** */


///////////////////////////////////////////////////////
// Function: loadBar(void)
//
// On bootup time we will show loading bar for defined BOOTTIME seconds
// This is interesting to avoid writing to APM during bootup if OSD's TX is connected
// After that, it continue in normal mode eg starting to listen MAVLink commands

#ifdef USE_WITH_MINRXOSD
#define barX 5
#define barY 13
#else
#define barX 5
#define barY 12
#endif

void loadBar() // change name due we don't have CLI anymore
{
    int waitTimer;
    byte barStep = 0;

    // Write plain panel to let users know what to do
    panBoot(barX, barY);

    delay(1000); // To give small extra waittime to users
    Serial.flush();

    // Our main loop to wait input from user.
    for (waitTimer = 0; waitTimer <= BOOTTIME; waitTimer++) {
        // How often we update our progress bar is depending on modulo
        if (waitTimer % (BOOTTIME / 7) == 0) {
            // Update bar itself
            osd.setPanel(barX + 12 + barStep, barY);
            osd.openPanel();
            osd.write('\xee');
            osd.closePanel();
            barStep++;
        }

        delay(1); // Minor delay to make sure that we stay here long enough
    }
}
