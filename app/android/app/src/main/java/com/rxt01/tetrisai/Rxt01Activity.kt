package com.rxt01.tetrisai

import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.rxt01.tetrisai.databinding.ActivityRxt01Binding

class Rxt01Activity : AppCompatActivity() {
    private lateinit var binding: ActivityRxt01Binding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityRxt01Binding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.buttongithub.setOnClickListener {
            val intent = Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/rxt01"))
            startActivity(intent)
        }
    }
}