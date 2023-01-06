package com.rxt01.tetrisai

import android.content.Intent
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.rxt01.tetrisai.databinding.ActivityCreditBinding
import com.rxt01.tetrisai.databinding.ActivityPlayBinding

class CreditActivity : AppCompatActivity() {
    private lateinit var binding: ActivityCreditBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityCreditBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.rxt01logo.setOnClickListener{
            val intent = Intent(this, Rxt01Activity::class.java)
            startActivity(intent)
        }
        binding.textViewrxt01.setOnClickListener{
            val intent = Intent(this, Rxt01Activity::class.java)
            startActivity(intent)
        }
        binding.textViewproject.setOnClickListener{
            val intent = Intent(this, Rxt01Activity::class.java)
            startActivity(intent)
        }
        binding.textversion.setOnClickListener {
            val intent = Intent(Intent.ACTION_VIEW, Uri.parse("https://rxt01.github.io/tetris-website/changelog.html"))
            startActivity(intent)
        }

    }
}