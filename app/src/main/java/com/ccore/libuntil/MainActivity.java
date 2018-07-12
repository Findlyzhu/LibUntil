package com.ccore.libuntil;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.ccore.skfjni.SKFJni;

import java.io.File;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private SKFJni  skfJni;
    private long    ret = 0;
    public static String innerSDPath = "";
    public static String outerSDPath = "";
    public static final String CONFIG_PATH = "/Android/data/com.ccore.libuntil";
    public static final String FILE = "/files/";
    private String fileDirPath = android.os.Environment
            .getExternalStorageDirectory().getAbsolutePath()// 得到外部存储卡的数据库的路径名
            + CONFIG_PATH + FILE;// 我要存储的目录

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getSdPath();

        skfJni = new SKFJni();

        ret = skfJni.SKF_SetAppPath(CONFIG_PATH.getBytes());// 得到外部存储卡的数据库的路径名)

        ret = skfJni.SKF_ConnectDev();
    }

    private void getSdPath() {
        getExternalFilesDir(null).getAbsolutePath();
        ArrayList<StorageInfo> sds = StorageInfo.getAvaliableStorages(this);
        if (sds != null && sds.size() > 0) {
            for (StorageInfo si : sds) {
                if (!si.isRemoveable) {
                    innerSDPath = si.path;
                    break;
                }
            }
            for (StorageInfo si : sds) {
                if (si.isRemoveable) {
                    outerSDPath = si.path;
                    break;
                }
            }
        }

        if (innerSDPath.isEmpty() && outerSDPath.isEmpty()) {
            innerSDPath = Environment.getExternalStorageDirectory().getPath();
            outerSDPath = Environment.getExternalStorageDirectory().getPath();

        } else if (innerSDPath.isEmpty()) {
            innerSDPath = Environment.getExternalStorageDirectory().getPath();
        }
        if (outerSDPath.isEmpty()) {
            outerSDPath = Environment.getExternalStorageDirectory().getPath();
        }

        if (innerSDPath.equals(outerSDPath)) {
            String Path = innerSDPath + CONFIG_PATH + "/";
            File f = new File(Path);
            if (!f.exists())
                f.mkdir();
        } else {
            String Path = innerSDPath + CONFIG_PATH + "/";
            File f = new File(Path);
            if (!f.exists())
                f.mkdir();

            Path = outerSDPath + CONFIG_PATH + "/";
            f = new File(Path);
            if (!f.exists())
                f.mkdir();
        }

        return;
    }
}
