package com.flightmanager.databaseservice.models;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;
import java.util.List;
import java.util.Set;

@Entity
@Table(name = "dispatchers")
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class DispatcherModel {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String firstName;
    private String lastName;
    private String email;
    @ElementCollection
    private Set<RoleModel> roles;
    private Boolean isBanned;
}
