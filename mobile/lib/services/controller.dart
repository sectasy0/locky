import 'package:http/http.dart' as http;

class ESPController {
  static final ESPController _inst = ESPController._internal();

  String _address;

  factory ESPController([String espAddress]) {
    _inst._address = espAddress;
    return _inst;
  }

  Future<http.Response> _request(String url) async {
    var response = await http.get(Uri.parse(url));
    print('Response status: ${response.statusCode}');
    print('Response body: ${response.body}');
  }

  bool checkConnection() {
    return true;
  }

  void open(String authToken) {
    var response = this._request(this._address + '/interact?state=open&authtoken='+ authToken);
  }

  void close(String authToken) {
    var response = this._request(this._address + '/interact?state=close&authtoken=' + authToken);
  }

  ESPController._internal();

}