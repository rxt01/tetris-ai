// Generated by view binder compiler. Do not edit!
package com.rxt01.tetrisai.databinding;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.viewbinding.ViewBinding;
import androidx.viewbinding.ViewBindings;
import com.rxt01.tetrisai.R;
import java.lang.NullPointerException;
import java.lang.Override;
import java.lang.String;

public final class ActivityCreditBinding implements ViewBinding {
  @NonNull
  private final ConstraintLayout rootView;

  @NonNull
  public final ImageView rxt01logo;

  @NonNull
  public final TextView textView2;

  @NonNull
  public final TextView textView6;

  @NonNull
  public final TextView textViewproject;

  @NonNull
  public final TextView textViewrxt01;

  @NonNull
  public final TextView textversion;

  private ActivityCreditBinding(@NonNull ConstraintLayout rootView, @NonNull ImageView rxt01logo,
      @NonNull TextView textView2, @NonNull TextView textView6, @NonNull TextView textViewproject,
      @NonNull TextView textViewrxt01, @NonNull TextView textversion) {
    this.rootView = rootView;
    this.rxt01logo = rxt01logo;
    this.textView2 = textView2;
    this.textView6 = textView6;
    this.textViewproject = textViewproject;
    this.textViewrxt01 = textViewrxt01;
    this.textversion = textversion;
  }

  @Override
  @NonNull
  public ConstraintLayout getRoot() {
    return rootView;
  }

  @NonNull
  public static ActivityCreditBinding inflate(@NonNull LayoutInflater inflater) {
    return inflate(inflater, null, false);
  }

  @NonNull
  public static ActivityCreditBinding inflate(@NonNull LayoutInflater inflater,
      @Nullable ViewGroup parent, boolean attachToParent) {
    View root = inflater.inflate(R.layout.activity_credit, parent, false);
    if (attachToParent) {
      parent.addView(root);
    }
    return bind(root);
  }

  @NonNull
  public static ActivityCreditBinding bind(@NonNull View rootView) {
    // The body of this method is generated in a way you would not otherwise write.
    // This is done to optimize the compiled bytecode for size and performance.
    int id;
    missingId: {
      id = R.id.rxt01logo;
      ImageView rxt01logo = ViewBindings.findChildViewById(rootView, id);
      if (rxt01logo == null) {
        break missingId;
      }

      id = R.id.textView2;
      TextView textView2 = ViewBindings.findChildViewById(rootView, id);
      if (textView2 == null) {
        break missingId;
      }

      id = R.id.textView6;
      TextView textView6 = ViewBindings.findChildViewById(rootView, id);
      if (textView6 == null) {
        break missingId;
      }

      id = R.id.textViewproject;
      TextView textViewproject = ViewBindings.findChildViewById(rootView, id);
      if (textViewproject == null) {
        break missingId;
      }

      id = R.id.textViewrxt01;
      TextView textViewrxt01 = ViewBindings.findChildViewById(rootView, id);
      if (textViewrxt01 == null) {
        break missingId;
      }

      id = R.id.textversion;
      TextView textversion = ViewBindings.findChildViewById(rootView, id);
      if (textversion == null) {
        break missingId;
      }

      return new ActivityCreditBinding((ConstraintLayout) rootView, rxt01logo, textView2, textView6,
          textViewproject, textViewrxt01, textversion);
    }
    String missingId = rootView.getResources().getResourceName(id);
    throw new NullPointerException("Missing required view with ID: ".concat(missingId));
  }
}