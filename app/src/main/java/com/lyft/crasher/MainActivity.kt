package com.lyft.crasher

import android.os.Bundle
import android.widget.Button
import com.bugsnag.android.Bugsnag
import com.bugsnag.android.Configuration
import androidx.appcompat.app.AppCompatActivity
import com.lyft.android.crashreporting.NdkCrashReporting
import java.io.File

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val crasher = NativeCrasher()

        findViewById<Button>(R.id.make_native_crash).setOnClickListener {
            crasher.makeNativeCrash()
        }

        findViewById<Button>(R.id.make_native_anr).setOnClickListener {
            crasher.makeNativeAnr()
        }


        val config = Configuration.load(this)
        config.setUser("123456", "joebloggs@example.com", "Joe Bloggs")
        config.addMetadata("user", "age", 31)

        Bugsnag.start(this, config)

        val crashLogsFile = File(application.cacheDir.absolutePath + "/crash-logs")
        crashLogsFile.mkdirs()

        val ndkCrashReporting = NdkCrashReporting()
        ndkCrashReporting.performNativeBugsnagSetup(
            crashLogsFile.absolutePath,
            sendEventsToBugsnag = false,
            cacheEvents = true,
            cacheFileCharLimit = 2000
        )

    }
}