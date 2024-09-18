package com.flightmanager.identityservice.api;

import com.flightmanager.identityservice.models.TokenResponse;
import com.flightmanager.identityservice.models.UserModel;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class AuthController {



    @GetMapping("")
    public ResponseEntity<TokenResponse> login() {}

    @PostMapping("")
    public ResponseEntity<TokenResponse> register(@RequestBody UserModel data) {}

    @GetMapping("")
    public ResponseEntity<Boolean> authorize(@RequestBody String token) {}


}
