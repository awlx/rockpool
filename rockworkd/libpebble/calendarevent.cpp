#include "calendarevent.h"

#include <QSettings>
#include <QFile>
#include <QTimeZone>

CalendarEvent::CalendarEvent():
    m_uuid(QUuid::createUuid())
{
}

bool CalendarEvent::isValid() const
{
    return !m_id.isNull();
}

QString CalendarEvent::id() const
{
    return m_id;
}

void CalendarEvent::setId(const QString &id)
{
    m_id = id;
}

QUuid CalendarEvent::uuid() const
{
    return m_uuid;
}

void CalendarEvent::generateNewUuid()
{
    m_uuid = QUuid::createUuid();
    m_reminderUuid = QUuid::createUuid();
}

QString CalendarEvent::title() const
{
    return m_title;
}

void CalendarEvent::setTitle(const QString &title)
{
    m_title = title;
}

QString CalendarEvent::description() const
{
    return m_description;
}

void CalendarEvent::setDescription(const QString &description)
{
    m_description = description;
}

QDateTime CalendarEvent::startTime() const
{
    return m_startTime;
}

void CalendarEvent::setStartTime(const QDateTime &startTime)
{
    m_startTime = startTime;
}

QDateTime CalendarEvent::endTime() const
{
    return m_endTime;
}

void CalendarEvent::setEndTime(const QDateTime &endTime)
{
    m_endTime = endTime;
}

QDateTime CalendarEvent::reminder() const {
    return m_reminder;
}

void CalendarEvent::setReminder(const QDateTime reminder) {
    m_reminder = reminder;
}

QUuid CalendarEvent::reminderUuid() const
{
    return m_reminderUuid;
}

QString CalendarEvent::location() const
{
    return m_location;
}

void CalendarEvent::setLocation(const QString &location)
{
    m_location = location;
}

QString CalendarEvent::calendar() const
{
    return m_calendar;
}

void CalendarEvent::setCalendar(const QString &calendar)
{
    m_calendar = calendar;
}

QString CalendarEvent::comment() const
{
    return m_comment;
}

void CalendarEvent::setComment(const QString &comment)
{
    m_comment = comment;
}

QStringList CalendarEvent::guests() const
{
    return m_guests;
}

void CalendarEvent::setGuests(const QStringList &guests)
{
    m_guests = guests;
}

bool CalendarEvent::recurring() const
{
    return m_recurring;
}

void CalendarEvent::setRecurring(bool recurring)
{
    m_recurring = recurring;
}

bool CalendarEvent::isAllDay() const
{
    return m_isAllDay;
}

void CalendarEvent::setIsAllDay(bool isAllDay)
{
    m_isAllDay = isAllDay;
}

bool CalendarEvent::operator==(const CalendarEvent &other) const
{
    // Storing a QDateTime to QSettings seems to lose time zone information. Lets ignore the time zone when
    // comparing or we'll never find ourselves again.
    QDateTime thisStartTime = m_startTime;
    if (other.startTime().timeSpec() == Qt::TimeZone)
        thisStartTime.setTimeZone(other.startTime().timeZone());
    QDateTime thisEndTime = m_endTime;
    if (other.endTime().timeSpec() == Qt::TimeZone)
        thisEndTime.setTimeZone(other.endTime().timeZone());
    QDateTime thisReminder = m_reminder;
        if (other.reminder().timeSpec() == Qt::TimeZone)
    thisReminder.setTimeZone(other.reminder().timeZone());
    return m_id == other.id()
            && m_title == other.title()
            && m_description == other.description()
            && thisStartTime == other.startTime()
            && thisEndTime == other.endTime()
            && thisReminder == other.reminder()
            && m_location == other.location()
            && m_calendar == other.calendar()
            && m_comment == other.comment()
            && m_guests == other.guests()
            && m_recurring == other.recurring()
            && m_isAllDay == other.isAllDay();
}

void CalendarEvent::diff(const CalendarEvent &other) const {
    QDateTime thisStartTime = m_startTime;
    if (other.startTime().timeSpec() == Qt::TimeZone)
        thisStartTime.setTimeZone(other.startTime().timeZone());
    QDateTime thisEndTime = m_endTime;
    if (other.endTime().timeSpec() == Qt::TimeZone)
        thisEndTime.setTimeZone(other.endTime().timeZone());
    QDateTime thisReminder = m_reminder;
        if (other.reminder().timeSpec() == Qt::TimeZone)
    thisReminder.setTimeZone(other.reminder().timeZone());

    if (m_id != other.id()) qDebug() << "id: " << m_id << " <> " << other.id();
    if (m_title != other.title()) qDebug() << "title: " << m_title << " <> " << other.title();
    if (m_description != other.description()) qDebug() << "description: " << m_description << " <> " << other.description();
    if (thisStartTime != other.startTime()) qDebug() << "startTime: " << thisStartTime << " <> " << other.startTime();
    if (thisEndTime != other.endTime()) qDebug() << "endTime: " << thisEndTime << " <> " << other.endTime();
    if (thisReminder != other.reminder()) qDebug() << "reminder: " << thisReminder << " <> " << other.reminder();
    if (m_location != other.location()) qDebug() << "location: " << m_location << " <> " << other.location();
    if (m_calendar != other.calendar()) qDebug() << "calendar: " << m_calendar << " <> " << other.calendar();
    if (m_comment != other.comment()) qDebug() << "comment: " << m_comment << " <> " << other.comment();
    if (m_guests != other.guests()) qDebug() << "guests: " << m_guests << " <> " << other.guests();
    if (m_recurring != other.recurring()) qDebug() << "recurring: " << m_recurring << " <> " << other.recurring();
    if (m_isAllDay != other.isAllDay()) qDebug() << "isAllDay: " << m_isAllDay << " <> " << other.isAllDay();
}

void CalendarEvent::saveToCache(const QString &cachePath) const
{
    QSettings s(cachePath + "/calendarevent-" + m_uuid.toString(), QSettings::IniFormat);
    s.setValue("id", m_id);
    s.setValue("uuid", m_uuid);
    s.setValue("title", m_title);
    s.setValue("description", m_description);
    s.setValue("startTime", m_startTime);
    s.setValue("endTime", m_endTime);
    s.setValue("location", m_location);
    s.setValue("calendar", m_calendar);
    s.setValue("comment", m_comment);
    s.setValue("guests", m_guests);
    s.setValue("recurring", m_recurring);
    s.setValue("isAllDay", m_isAllDay);
    s.setValue("reminder", m_reminder);
    s.setValue("reminderId", m_reminderUuid);
}

void CalendarEvent::loadFromCache(const QString &cachePath, const QString &uuid)
{
    m_uuid = uuid;
    QSettings s(cachePath + "/calendarevent-" + m_uuid.toString(), QSettings::IniFormat);
    m_id = s.value("id").toString();
    m_title = s.value("title").toString();
    m_description = s.value("description").toString();
    m_startTime = s.value("startTime").toDateTime();
    m_endTime = s.value("endTime").toDateTime();
    m_location = s.value("location").toString();
    m_calendar = s.value("calendar").toString();
    m_comment = s.value("comment").toString();
    m_guests = s.value("guests").toStringList();
    m_recurring = s.value("recurring").toBool();
    m_isAllDay = s.value("isAllDay").toBool();
    m_reminder = s.value("reminder").toDateTime();
    m_reminderUuid = s.value("reminderId").toUuid();
}

void CalendarEvent::removeFromCache(const QString &cachePath) const
{
    QFile::remove(cachePath + "/calendarevent-" + m_uuid.toString());
}

