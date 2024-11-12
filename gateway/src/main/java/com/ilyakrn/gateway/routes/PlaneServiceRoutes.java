package com.ilyakrn.gateway.routes;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Configuration
public class PlaneServiceRoutes {
    @Getter
    @Value("${url.plane-service}")
    private String url;

    public String[] getMappings() {
        return new String[]{

        };
    }
}
