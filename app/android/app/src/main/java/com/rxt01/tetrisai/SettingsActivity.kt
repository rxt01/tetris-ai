package com.rxt01.tetrisai

import android.Manifest
import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.core.app.ActivityCompat
import com.rxt01.tetrisai.databinding.ActivityAiBinding
import com.rxt01.tetrisai.databinding.ActivitySettingsBinding

class SettingsActivity : AppCompatActivity() {
    private lateinit var binding: ActivitySettingsBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivitySettingsBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.buttonsave.setOnClickListener {
            requestPermission()
        }
    }

    private fun hasWriteExeternalStoragePermission()=
        ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED
    private fun requestPermission(){
        var permissionToRequest = mutableListOf<String>()
        if (!hasWriteExeternalStoragePermission()){
            permissionToRequest.add(Manifest.permission.WRITE_EXTERNAL_STORAGE)
        }
        if(permissionToRequest.isNotEmpty()){
            ActivityCompat.requestPermissions(this, permissionToRequest.toTypedArray(), 0)
        }
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == 0 && grantResults.isNotEmpty()){
            for (i in grantResults.indices){
                if (grantResults[i] == PackageManager.PERMISSION_GRANTED){
                    Log.d("permission", "${permissions[i]} granted")
                }else{
                    Toast.makeText(this, "permission needed to save the settings", 1).show()
                }
            }
        }
    }
}