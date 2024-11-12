package com.flightmanager.identityservice.api;

import com.flightmanager.identityservice.exception.HTTP400Exception;
import com.flightmanager.identityservice.models.AuthorizeRequest;
import com.flightmanager.identityservice.models.TokenRequest;
import com.flightmanager.identityservice.models.TokenResponse;
import com.flightmanager.identityservice.models.UserModel;
import com.flightmanager.identityservice.service.AuthService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@Slf4j
@RestController
public class AuthController {

    @Autowired
    private AuthService authService;

    @PostMapping("${mapping.auth.login}")
    public ResponseEntity<TokenResponse> login(@RequestBody TokenRequest tokenRequest) {
        try {
            if (tokenRequest == null ||
                    tokenRequest.getEmail() == null ||
                    tokenRequest.getEmail().isEmpty() ||
                    tokenRequest.getPassword() == null ||
                    tokenRequest.getPassword().isEmpty()
            ) return ResponseEntity.status(400).build();
            TokenResponse response = authService.login(tokenRequest.getEmail(), tokenRequest.getPassword());
            if (response == null)
                return ResponseEntity.status(401).build();
            log.info("login auth successful: id=" + model.getId());
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            log.warn("login auth failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.auth.register}")
    public ResponseEntity<TokenResponse> register(@RequestBody UserModel data) {
        try {
            TokenResponse response = authService.register(data);
            if (response == null)
                return ResponseEntity.status(401).build();
            return ResponseEntity.ok(response);
        } catch (HTTP400Exception e){
            log.info("register auth successful: id=" + model.getId());
            return ResponseEntity.status(400).build();
        } catch (Exception e) {
            log.warn("register auth failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.auth.authorize}")
    public ResponseEntity<Boolean> authorize(@RequestBody AuthorizeRequest authorizeRequest) {
        try {
            log.info("authorize auth successful: id=" + model.getId());
            return ResponseEntity.ok(authService.authorize(authorizeRequest.getToken(), authorizeRequest.getPermissions()));
        } catch (Exception e) {
            log.warn("authorize auth failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.auth.id-by-token}")
    public ResponseEntity<Long> getIdByToken(@RequestBody String token) {
        try {
            Long id = authService.getIdFromToken(token);
            if (id == null)
                return ResponseEntity.status(401).build();
            log.info("id-by-token successful: id=" + model.getId());
            return ResponseEntity.ok(id);
        } catch (Exception e) {
            log.warn("id-by-token auth failed: " + e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }


}
