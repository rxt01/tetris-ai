package com.rxt01.tetrisai

import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.rxt01.tetrisai.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.buttonupdate.setOnClickListener {
            val intent = Intent(Intent.ACTION_VIEW, Uri.parse("https://rxt01.github.io/tetris-website/android-download.html"))
            startActivity(intent)
        }
        binding.buttonsettings.setOnClickListener {
            val intent = Intent(this, SettingsActivity::class.java)
            startActivity(intent)
        }
        binding.buttonplay.setOnClickListener {
            val intent = Intent(this, PlayActivity::class.java)
            startActivity(intent)
        }
        binding.buttonai.setOnClickListener {
            Toast.makeText(this, "Feature Not Implemented Yet", 1).show()
            //this is only in the test build, remove before releasing//
            val intent = Intent(this, AIActivity::class.java)
            startActivity(intent)
            //-------------------------------------------------------//
        }
        binding.buttoncredit.setOnClickListener {
            val intent = Intent(this, CreditActivity::class.java)
            startActivity(intent)
        }

    }
}