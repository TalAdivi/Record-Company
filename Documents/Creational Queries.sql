/* Create musician table */

CREATE TABLE `musician` (
  `id_musician` INT NOT NULL,
  `Name` VARCHAR(256) NOT NULL,
  `Address` VARCHAR(256) NOT NULL,
  `Phone` VARCHAR(256) NOT NULL,
  `Skill` VARCHAR(256) NOT NULL,
  PRIMARY KEY (`id_musician`));

/* Create instrument table */

CREATE TABLE `instrument` (
  `I_id` INT NOT NULL UNIQUE,
  `Brand` VARCHAR(256) NOT NULL,
  `Type` VARCHAR(256) NOT NULL,
  PRIMARY KEY (`I_id`, `Brand`, `Type`));
  
/* Create track table */

CREATE TABLE `track` (
  `T_id` INT NOT NULL,
  `Name` VARCHAR(256) NOT NULL,
  `Music_Compuser` VARCHAR(256) NULL,
  `Length` INT NOT NULL,
  `Lyrics_Composer` VARCHAR(256) NULL,
  `Date` VARCHAR(256) NOT NULL,
  `Genre` VARCHAR(256) NOT NULL,
  `Technician` VARCHAR(256) NOT NULL,
  PRIMARY KEY (`T_id`));

/* Create album table */

CREATE TABLE `album` (
  `A_id` INT NOT NULL,
  `Name` VARCHAR(256) NOT NULL,
  `S_Date` VARCHAR(256) NOT NULL,
  `E_Date` VARCHAR(256) NOT NULL,
  `Tracks_Number` INT NOT NULL,
  PRIMARY KEY (`A_id`));

/* Create producer table */

CREATE TABLE `producer` (
  `p_ID` INT NOT NULL,
  `Name` VARCHAR(256) NOT NULL,
  PRIMARY KEY (`p_ID`));

/* Create musician x instrument relation table */

CREATE TABLE `musician_instrument` (
  `m_ID` INT NOT NULL,
  `i_ID` INT NOT NULL,
  PRIMARY KEY (`i_ID`, `m_ID`),
  INDEX `MI_mID_idx` (`m_ID` ASC) VISIBLE,
  CONSTRAINT `MI_mID`
    FOREIGN KEY (`m_ID`)
    REFERENCES `musician` (`id_musician`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `MI_iID`
    FOREIGN KEY (`i_ID`)
    REFERENCES `instrument` (`I_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);

/* Create musician x track relation table */

CREATE TABLE `musician_tracks` (
  `m_ID` INT NOT NULL,
  `t_ID` INT NOT NULL,
  PRIMARY KEY (`m_ID`, `t_ID`),
  INDEX `MT_tID_idx` (`t_ID` ASC) VISIBLE,
  CONSTRAINT `MT_mID`
    FOREIGN KEY (`m_ID`)
    REFERENCES `musician` (`id_musician`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `MT_tID`
    FOREIGN KEY (`t_ID`)
    REFERENCES `track` (`T_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);

/* Create album x track relation table */

CREATE TABLE `album_track` (
  `t_ID` INT NOT NULL,
  `a_ID` INT NOT NULL,
  PRIMARY KEY (`t_ID`, `a_ID`),
  INDEX `AT_aID_idx` (`a_ID` ASC) VISIBLE,
  CONSTRAINT `AT_tID`
    FOREIGN KEY (`t_ID`)
    REFERENCES `track` (`T_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `AT_aID`
    FOREIGN KEY (`a_ID`)
    REFERENCES `album` (`A_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);

/* Create album x producer relation table */

CREATE TABLE `album_producer` (
  `a_ID` INT NOT NULL,
  `p_ID` INT NOT NULL,
  PRIMARY KEY (`a_ID`, `p_ID`),
  INDEX `AP_pID_idx` (`p_ID` ASC) VISIBLE,
  CONSTRAINT `AP_aID`
    FOREIGN KEY (`a_ID`)
    REFERENCES `album` (`A_id`)\
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `AP_pID`
    FOREIGN KEY (`p_ID`)
    REFERENCES `producer` (`p_ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);