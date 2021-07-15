import 'package:shared_preferences/shared_preferences.dart';
import 'package:locky/globals.dart' as globals;

class PreferenceUtils {
  static Future<SharedPreferences> get _instance async => _prefsInstance ??= await SharedPreferences.getInstance();
  static SharedPreferences _prefsInstance;

  static Future<SharedPreferences> init() async {
    List<String> keys = ["defaultAuthToken", "defaultEspAddress", "defaultWifiName"];

    _prefsInstance = await _instance;

    for(var key in keys) {
      print(getString(key));
      if(getString(key) == "") {
        setString(key, globals.settings[key]);
      }
    }

    return _prefsInstance;
  }

  static String getString(String key, [String defValue]) {
    return _prefsInstance.getString(key) ?? defValue ?? "";
  }

  static Future<bool> setString(String key, String value) async {
    var prefs = await _instance;
    return prefs?.setString(key, value) ?? Future.value(false);
  }

}