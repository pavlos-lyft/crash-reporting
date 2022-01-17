package com.lyft.crasher

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

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
    }
}