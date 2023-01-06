package com.rxt01.tetrisai

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.rxt01.tetrisai.databinding.ActivityAiBinding
import com.rxt01.tetrisai.databinding.ActivitySettingsBinding

class AIActivity : AppCompatActivity() {
    private lateinit var binding: ActivityAiBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityAiBinding.inflate(layoutInflater)
        setContentView(binding.root)
    }
}